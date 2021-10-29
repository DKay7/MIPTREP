#include "asm.h"
#include "../libs/bin_text_lib/binlib.h"
#include "../defines_and_setups/asm_setup.h"
#include "../defines_and_setups/errors.h"
#include "../defines_and_setups/cpu_setup.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CompileCode (AsmCompiler* acc, Text* code, const char* bin_filename, const char* listing_filename)
{
    FILE* listing_file = fopen (listing_filename, "w");

    if (listing_file == NULL || ferror (listing_file))
    {   
        acc->asm_errno |= ASMCC_FILE_OPENING_ERR;
        return acc->asm_errno;
    }

    for (size_t i = 0; i < code->non_empty_lines; i++)
    {   
        if (ParseCommand (acc, code->lines[i].ptr, listing_file) != ASMCC_OK)
        {   
            AsmDumpFunction (acc, listing_file);
            return acc->asm_errno;
        }
    }

    BinHeader bh = {};
    BinHeaderCtor (&bh, SIGNATURE, CC_VERSION);
    WriteToBinary (&bh, acc->cmd_array, acc->cmd_array_size, bin_filename);
    
    return acc->asm_errno;
}   

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmCompilerCtor (AsmCompiler* acc, size_t cmd_array_size)
{
    acc->ip = 0;
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

        if (cmd_name == NULL || *cmd_name == '\0')
        {
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
    arg_t arg = 0;
    char* reg_arg = NULL;
    char* is_memory = NULL;
    acc->ip -= sizeof (unsigned char); // back to last command id
    unsigned char command_id = acc->cmd_array[acc->ip];

    if ((arg_code & RAM_VALUE) && (is_memory = strchr(command, '[')))
    {   
        command = is_memory + 1;
        char* mem_end = strchr(command, ']');
        
        if (!mem_end)
        {   
            acc->asm_errno |= ASMCC_ERR_READING_CMD_ARGS;
            return acc->asm_errno;
        }

        *mem_end = '\0';

        arg_code |= IMMEDIATE_CONST; // if it's ram then arg may be IM or REGVAL even
        arg_code |= REGISTER_VALUE;  // if it couldn't be IM or REGVAL without RAM

        command_id |= RAM_VALUE;
    }

    if ((arg_code & IMMEDIATE_CONST) && sscanf (command, " %lf", &arg) > 0)
    {   
        command_id |= IMMEDIATE_CONST;
        acc->cmd_array[acc->ip] = command_id;

        *(arg_t*) (acc->cmd_array + acc->ip + sizeof (unsigned char)) = arg;
        acc->ip += sizeof (unsigned char) + sizeof (arg_t);
        
        fprintf (listing_file, "%02X\t|\t", command_id);
        PrintValToListing (listing_file, &arg, sizeof (arg_t));
    }

    else if ((arg_code & REGISTER_VALUE) && sscanf (command, " %ms", &reg_arg) > 0)
    {   
        command_id |= REGISTER_VALUE;
        acc->cmd_array[acc->ip] = command_id;
        acc->ip += sizeof (unsigned char);

        fprintf (listing_file, "%02X\t|\t", command_id);

        #include "compare_registers_defines.h"

        free (reg_arg);
    }

    else if ((arg_code & OPTIONAL_ARG) == 0)
    {
        // argument is optional
        acc->cmd_array[acc->ip] = command_id;
        acc->ip += sizeof (unsigned char);
        fprintf (listing_file, "%02X\t|\t", command_id);
        return acc->asm_errno;
    }
    
    else
    {   
        acc->asm_errno |= ASMCC_ERR_READING_CMD_ARGS;
    }

    return acc->asm_errno;
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

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmUnitTest ()
{   
    Text code = {};
    TextCtor (&code, "asm_file.asm");

    AsmCompiler acc = {};
    long unsigned int cmd_arr_size = FindCmdArraySize (&code);
    AsmCompilerCtor (&acc, cmd_arr_size);

    CompileCode (&acc, &code, "asm_result.mc", "asm.lst");

    TextDtor (&code);
    AsmCompilerDtor (&acc);

    return 0;
}