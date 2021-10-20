#include "asm.h"
#include "../libs/bin_text_lib/binlib.h"
#include "../defines_and_setups/cmd_setup.h"
#include "../defines_and_setups/proc_errors.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <cstddef>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CompileCode (Text* code, const char* bin_filename, const char* listing_filename)
{
    AsmCompiler acc = {};
    int cmd_arr_size = FindCmdArraySize (code);
    AsmCompilerCtor (&acc, cmd_arr_size);

    FILE* listing_file = fopen (listing_filename, "w");

    if (ferror (listing_file) || listing_file == NULL)
    {   
        acc.asm_errno |= ASMCC_ERR_OPENING_FILE;
        
        int asm_errno = acc.asm_errno;
        AsmCompilerDtor (&acc);
        return asm_errno;
    }

    for (size_t i = 0; i < code->non_empty_lines; i++)
    {   
        if (ParseCommand (&acc, code->lines[i].ptr, listing_file) != ASMCC_OK)
        {   
            // TODO AsmDump to listing file
            fprintf (listing_file, "\nERROR!\nERROR NUM: %08X", acc.asm_errno);

            int asm_errno = acc.asm_errno;
            AsmCompilerDtor (&acc);
            return asm_errno;
        }
    }

    BinHeader bh = {};
    BinHeaderCtor (&bh, SIGNATURE, CC_VERSION);
    WriteToBinary (&bh, acc.cmd_array, cmd_arr_size, bin_filename);
    
    int asm_errno = acc.asm_errno;
    AsmCompilerDtor (&acc);
    return asm_errno;
}   

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmCompilerCtor (AsmCompiler* acc, int cmd_array_size)
{
    acc->ip = 0;
    acc->asm_errno = ASMCC_OK;
    acc->cmd_array = (unsigned char*) calloc (1, cmd_array_size);
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

    char* cmd_name;
    int shift = 0;
    sscanf (command, " %ms%n ", &cmd_name, &shift);

    if (*cmd_name == '\0')
    {
        return acc->asm_errno;
    }

    #include "read_command_defines.h"

    return acc->asm_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FindCmdArraySize (Text* code)
{   
    int num_bytes = 0;

    for (size_t i = 0; i < code->non_empty_lines; ++i)
    {
        char* is_comment = strchr (code->lines[i].ptr, COMMENT_SYMBOL);
        if (is_comment)
        {
            *is_comment = '\0';
        }

        char* cmd_name;
        sscanf (code->lines[i].ptr, " %ms ", &cmd_name);

        if (*cmd_name == '\0')
        {
            continue;
        }

        #include "find_arr_size_defines.h"
    }

    return num_bytes;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetArg (AsmCompiler* acc, char* command, FILE* listing_file)
{   
    arg_t arg = 0;
    if (sscanf (command, " %lf", &arg) > 0)
    {   
        *(arg_t*) (acc->cmd_array + acc->ip) = arg;
        acc->ip += sizeof (arg_t);
        
        PrintValToListing (listing_file, &arg, sizeof (arg_t));
        return acc->asm_errno;
    }
    
    return ASMCC_ERR_READING_CMD_ARGS;
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

int AsmUnitTest ()
{   
    Text code = {};
    TextCtor (&code, "asm_file.asm");
    CompileCode (&code, "asm_result.mc", "asm.lst");

    TextDtor (&code);

    return 0;
}