#include "asm.h"
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "../machine/proc.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmParseCommand(double* cmd_array, String* command_and_args, int* pc)
{   
    assert (command_and_args);

    char* command_name = NULL;
    int num_words_in_cmd = sscanf (command_and_args->start, "%ms", &command_name);

    if (num_words_in_cmd <= 0)
    {
        proc_errno = proc_errno | ASM_ERR_READING_CMD_NAME;
        return proc_errno;
    }

    if (strcmp (command_name, "pop") == 0)
    {     
        // POP CASE
        cmd_array[*pc] = ASM_POP_CODE; 
    }

    else if (strcmp (command_name, "push") == 0)
    {
        // PUSH case;
        stack_type arg = STACK_DATA_POISON;
        int num_readed_symbols = sscanf (command_and_args->start, "push %lf", &arg);
        CHECK_ARGS_NUM (num_readed_symbols, 1);

        cmd_array[*pc] = ASM_POP_CODE;
        *pc += 2;
    }

    else if (strcmp (command_name, "add") == 0)
    {
        // ADD case;
        cmd_array[*pc] = ASM_ADD_CODE;
        *pc += 1;

    }

    else if (strcmp (command_name, "sub") == 0)
    {
        // SUB case;
        cmd_array[*pc] = ASM_SUB_CODE;
        *pc += 1;
    }

    else if (strcmp (command_name, "mul") == 0)
    {
        // MUL case;
        cmd_array[*pc] = ASM_MUL_CODE;
        *pc += 1;
    }

    else if (strcmp (command_name, "div") == 0)
    {
        // DIV case;
        cmd_array[*pc] = ASM_DIV_CODE;
        *pc += 1;
    }
    
    else if (strcmp (command_name, "dump") == 0)
    {
        // DUMP case;
        cmd_array[*pc] = ASM_DUMP_CODE;
        *pc += 1;
    }

    else if (strcmp (command_name, "out") == 0)
    {
        // OUT case;
        cmd_array[*pc] = ASM_OUT_CODE;
        *pc += 1;
    }

    else if (strcmp (command_name, "hlt") == 0)
    {
        // HLT case;
        cmd_array[*pc] = ASM_HLT_CODE;
        *pc += 1;
    }
    

    else if (strcmp (command_name, "validate") == 0)
    {
        // VALIDATE case;
        cmd_array[*pc] = ASM_VALIDATE_CODE;
        *pc += 1;
    }

    else
    {
        proc_errno = proc_errno | ASM_ERR_READING_CMD_NAME;
    }

    free (command_name);

    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmProcessFile(const char* filename_to_read, const char* filename_to_write)
{
    assert (filename_to_read);
    assert (filename_to_write);

    FILE* file_to_read = fopen(filename_to_read, "r"); 

    if (!file_to_read || ferror (file_to_read))
    {
        proc_errno = proc_errno | ASM_FILE_OPENING_ERR;
        return proc_errno;
    }

    size_t num_symbols = CountSymbols (file_to_read);
    char* file_buffer = ReadFileToBuffer (file_to_read, num_symbols);
    size_t num_lines = CountLines (file_buffer);

    String** ptr_array = (String**) calloc (num_lines, sizeof (String*));
    String* str_array = (String*) calloc (num_lines, sizeof (String));
    
    OneginFillPArray (file_buffer, ptr_array, str_array, num_lines, num_symbols);

    double* cmd_array = (double*) calloc (num_lines, sizeof (double) + sizeof (int)); //TODO if we want to make char array which size should it be?
    int program_counter = 0;

    for (size_t i = 0; i < num_lines; i ++)
    {   
        AsmParseCommand (cmd_array, ptr_array[i], &program_counter);
    }

    FILE* file_to_write = fopen(filename_to_write, "wb");

    if (!file_to_write || ferror (file_to_write))
    {
        proc_errno = proc_errno | ASM_FILE_OPENING_ERR;
        return proc_errno;
    }

    fwrite (cmd_array, sizeof (double), num_lines, file_to_write);

    free (ptr_array);
    free (str_array);
    free (file_buffer);

    return proc_errno;
}

int AsmUnitTest ()
{
    AsmProcessFile ("asm_file.asm", "asm_result.asmmc");

    return proc_errno;
}