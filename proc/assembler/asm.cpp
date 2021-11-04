#include "asm.h"
#include "../libs/bin_text_lib/binlib.h"
#include "../defines_and_setups/asm_setup.h"
#include "../defines_and_setups/errors.h"
#include "../defines_and_setups/cpu_setup.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CompileCode (AsmCompiler* acc, Text* code, const char* bin_filename, const char* listing_filename)
{   
    FILE* listing_file = fopen (listing_filename, "w");
    CHECK_FILE_OPENED (listing_file, "CompileCode", acc->asm_errno);

    for (int num_runnings = 0; num_runnings < TOTAL_NUM_RUNS; ++num_runnings)
    {   
        for (size_t i = 0; i < code->non_empty_lines; i++)
        {   
            if (ParseCommand (acc, code->lines[i].ptr, listing_file) != ASMCC_OK)
            {   
                AsmDumpFunction (acc, listing_file);
                CLOSE_FILE (listing_file, "CompileCode",  acc->asm_errno);
                return acc->asm_errno;
            }
        }

        fseek (listing_file, 0, SEEK_SET);
        acc->ip = 0;
    }

    if (CheckAllLabelsResoled (acc) != ASMCC_OK)
    {       
        AsmDumpFunction (acc, listing_file);
        CLOSE_FILE (listing_file, "CompileCode",  acc->asm_errno);
        return acc->asm_errno;
    }


    CLOSE_FILE (listing_file, "CompileCode",  acc->asm_errno);

    BinHeader bh = {};
    BinHeaderCtor (&bh, SIGNATURE, CC_VERSION);
    WriteToBinary (&bh, acc->cmd_array, acc->cmd_array_size, bin_filename);

    return acc->asm_errno;
}   

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CheckAllLabelsResoled (AsmCompiler* acc)
{
    for (long unsigned i = 0; i < acc->cur_label_index; i++)
    {
        if (acc->labels_table[i].ip < 0)
        {   
            acc->asm_errno |= ASMCC_LABEL_NOT_RESOLWED;
        }
    }

    return acc->asm_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmCompilerCtor (AsmCompiler* acc, size_t cmd_array_size)
{
    acc->ip = 0;
    acc->cur_label_index = 0;
    acc->asm_errno = ASMCC_OK;
    acc->cmd_array = (unsigned char*) calloc (1, cmd_array_size);
    acc->cmd_array_size = cmd_array_size;

    return acc->asm_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void AsmCompilerDtor (AsmCompiler* acc)
{
    assert (acc);
    assert (acc->cmd_array);

    free (acc->cmd_array);
}


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ParseCommand (AsmCompiler* acc, char* command, FILE* listing_file)
{
    assert (acc);
    assert (command);

    char* is_comment = strchr (command, COMMENT_SYMBOL);
    if (is_comment)
    {
        *is_comment = '\0';
    }

    char* cmd_name = NULL;
    int shift = 0;
    sscanf (command, " %ms%n ", &cmd_name, &shift);
    if (cmd_name == NULL || *cmd_name == '\0')
    {
        return acc->asm_errno;
    }

    #include "read_command_defines.h"

    free (cmd_name);
    return acc->asm_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

ssize_t FindCmdArraySize (Text* code)
{   
    ssize_t num_bytes = 0;

    for (size_t i = 0; i < code->non_empty_lines; ++i)
    {
        char* is_comment = strchr (code->lines[i].ptr, COMMENT_SYMBOL);
        if (is_comment)
        {
            *is_comment = '\0';
        }

        char* cmd_name = NULL;
        sscanf (code->lines[i].ptr, " %ms", &cmd_name);

        if (cmd_name == NULL || *cmd_name == '\0' || strchr (cmd_name, ':'))
        {   
            free (cmd_name);    
            continue;
        }

        #include "find_arr_size_defines.h"

        free (cmd_name);    
    }

    return num_bytes;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetArg (AsmCompiler* acc, char* command, int arg_code, FILE* listing_file)
{   
    acc->ip -= sizeof (unsigned char); // back to last command id
    unsigned char command_id = acc->cmd_array[acc->ip];

    arg_t arg = 0;
    char* reg_arg = NULL;
    char* is_memory = NULL;
    int is_label = 0;
    char* label = NULL;

    if ((arg_code & RAM_VALUE) && (is_memory = strchr(command, '[')))
    {   
        // ram value
        command = is_memory + 1;
        is_memory = strchr(command, ']'); // check memory end
        
        if (!is_memory)
        {   
            acc->asm_errno |= ASMCC_ERR_READING_CMD_ARGS;
            return acc->asm_errno;
        }

        *is_memory = '\0';

        arg_code |= IMMEDIATE_CONST; // if it's ram then arg may be IM or REGVAL even
        arg_code |= REGISTER_VALUE;  // if it couldn't be IM or REGVAL without RAM

        command_id |= RAM_VALUE;
    }

    if ((arg_code & IMMEDIATE_CONST) && sscanf (command, " %lf", &arg) > 0)
    {   
        // immediate const value
        command_id |= IMMEDIATE_CONST;
        acc->cmd_array[acc->ip] = command_id;
        acc->ip += sizeof (unsigned char);

        *(arg_t*) &(acc->cmd_array[acc->ip]) = arg;
        acc->ip += sizeof (arg_t);
        
        fprintf (listing_file, "%2X\t|\t", command_id);
        PrintValToListing (listing_file, &arg, sizeof (arg_t));
    }

    else if ((arg_code & REGISTER_VALUE) && sscanf (command, " %ms", &reg_arg) > 0)
    {   
        // register value
        command_id |= REGISTER_VALUE;
        acc->cmd_array[acc->ip] = command_id;
        acc->ip += sizeof (unsigned char);
        fprintf (listing_file, "%2X\t|\t", command_id);

        #include "compare_registers_defines.h"

        free (reg_arg);
    }
    
    else if ((is_label = sscanf (command, "%ms", &label)) > 0)
    {   
        // label (jump) case
        arg_t new_ip = (arg_t) GetLabelNum (acc, label);
        command_id |= IMMEDIATE_CONST;
        acc->cmd_array[acc->ip] = command_id;
        acc->ip += sizeof (unsigned char);

        *(arg_t*) (acc->cmd_array + acc->ip) = new_ip;
        acc->ip += sizeof (arg_t);

        fprintf (listing_file, "%2X\t|\t", command_id);
        PrintValToListing (listing_file, &new_ip, sizeof (arg_t));

        free (label);
    }

    else if ((arg_code & OPTIONAL_ARG) == 0)
    {
        // argument is optional 
        acc->cmd_array[acc->ip] = command_id;
        acc->ip += sizeof (unsigned char);
        fprintf (listing_file, "%2X\t|\t", command_id);
        return acc->asm_errno;
    }   

    else
    {   
        acc->asm_errno |= ASMCC_ERR_READING_CMD_ARGS;
    }

    if (is_memory)
    {
        *is_memory = ']'; // return symbol back for further compilation iterations
    }

    return acc->asm_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CheckAndProcessLabel (AsmCompiler* acc, char* command, FILE* listing_file)
{   
    char* is_label = NULL;
    if ((is_label = strchr (command, ':')))
    {   
        *is_label = '\0';
        char* label_without_spaces = NULL;
        sscanf (command, " %ms", &label_without_spaces);

        if (!isspace (*(is_label - 1)))
        {   
            fprintf (listing_file, "%-32s:\t|\t%02lX\t|\tLB\t|\t\n", command, acc->ip);
            WriteLabelToTable (acc, label_without_spaces, acc->ip);
            *is_label = ':';
            free (label_without_spaces);
            return 1;
        }
        
        free (label_without_spaces);
    }

    return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int  GetLabelNum (AsmCompiler* acc, char* label_name)
{
    int lbl_index = GetLabelByName (acc, label_name);
    
    if (lbl_index < 0)
    {
        WriteLabelToTable (acc, label_name, -1);
        return -1;
    }
    
    return acc->labels_table[lbl_index].ip;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void WriteLabelToTable (AsmCompiler* acc, char* label_name, int ip)
{   
    int lbl_index = GetLabelByName (acc, label_name);
    
    if (lbl_index < 0)
    {   
        Label lbl = {};
        strcpy (lbl.label, label_name);
        lbl.ip = ip;
        acc->labels_table [acc->cur_label_index] = lbl;
        acc->cur_label_index += 1;
        return;
    }

    acc->labels_table [lbl_index].ip = ip;
    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int  GetLabelByName (AsmCompiler* acc, char* label_name)
{
    for (unsigned int i = 0; i < acc->cur_label_index; i++)
    {
        if (strcmp  (label_name, acc->labels_table[i].label) == 0)
        {
            return i;
        }
    }

    return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintValToListing (FILE* listing_file, void* val, size_t type_size)
{   
    unsigned char* data = (unsigned char*) val;

    for (size_t i = 0; i < type_size; i++)
    {
        fprintf (listing_file, "%02X ", data[i]);
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void AsmDumpFunction (AsmCompiler* acc, FILE* logfile)
{   
    assert (acc);
    assert (logfile);

    int err_code = acc->asm_errno;

    if (err_code == ASMCC_OK)
    {
        fprintf (logfile, "\nAssembler is OK!\n");
    }

    if (err_code != ASMCC_OK)
    {
        fprintf (logfile, "\nOne or more errors were reached while compiling code.\n"
                    "Here they are:\n\n");
    }

    #include "dump_errors_defines.h"

    if (err_code != 0)
    {
        fprintf (logfile, "Unknown error with code %X", err_code);
    }

    if (acc->asm_errno & ASMCC_LABEL_NOT_RESOLWED)
    {   
        fprintf (logfile, "\nLabels table:\n");
        for (long unsigned i = 0; i < acc->cur_label_index; i ++)
        {
            fprintf (logfile, "\tLabel: %s, ip: %ld\n", acc->labels_table[i].label, acc->labels_table[i].ip);
        }
    }


    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetOutputFileNames (char* input, char* output, char* listing, int len)
{
    assert (input);
    assert (output);
    assert (listing);

    strncpy (output, input, len - 3);
    strncpy (listing, input, len - 3);
    char* dot_output = strchr(output, '.');
    char* dot_listing = strchr(listing, '.');

    if (!dot_listing || !dot_output)
    {
        return -1;
    }

    *(dot_output + 1) = 'm';
    *(dot_output + 2) = 'c';
    *(dot_output + 3) = '\0';

    *(dot_listing + 1) = 'l';
    *(dot_listing + 2) = 's';
    *(dot_listing + 3) = 't';
    *(dot_listing + 4) = '\0';

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
