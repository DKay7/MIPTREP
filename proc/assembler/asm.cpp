#include "asm.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include "../machine/proc.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmGetArg (char* args_str, double* arg)
{   
    int num_readed_symbols = 0;
    sscanf (args_str, " %lf %n", arg, &num_readed_symbols);

    return num_readed_symbols;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmCheckCommand (char* command_and_args, const char* command_name, int command_len)
{   
    if (strncmp (command_and_args, command_name, command_len) == 0)
    {   
        command_and_args += command_len;
        return AsmCheckCmdEnd (command_and_args); 
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmCheckCmdEnd (const char* command_and_args)
{   
    return *command_and_args == '\0' || *command_and_args == ';' || *command_and_args == '\n' || *command_and_args == ' ';
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmParseCommand (void* cmd_array, char* command_and_args, int* pc, FILE* listing_f)
{   
    assert (command_and_args);
    assert (listing_f);
    assert (cmd_array);


    #define DEF_COMMAND(name, n_args, _id, command_name, ...)    \
    if (AsmCheckCommand (command_and_args, command_name, strlen (command_name))) \
    { \
        int id = _id; \
        fprintf (listing_f, "%-32s\t|\t", command_and_args); \
        AsmPprintArgLst (listing_f, pc, sizeof (int)); \
        fprintf (listing_f, "\t|\t"); \
        AsmPprintArgLst (listing_f, &id, sizeof (unsigned char)); \
        fprintf (listing_f, "\t|\t"); \
        \
        ((unsigned char*)cmd_array)[*pc] = (unsigned char)(id); \
        (*pc) += sizeof (unsigned char); \
        \
        stack_type arg = STACK_DATA_POISON;     \
        int num_readed_symbols = 0;          \
        command_and_args += strlen (command_name); \
        \
        for (int i = 0; i < n_args; i++)     \
        {   num_readed_symbols = AsmGetArg (command_and_args, &arg);\
            AsmPprintArgLst (listing_f, &arg, sizeof (double)); \
            \
            *(double*)((unsigned char*)cmd_array + *pc) = (double)arg; \
            command_and_args += num_readed_symbols; \
            (*pc) += sizeof (double); \
        }   \
        fprintf (listing_f, "\n");\
        } \
        else

    #include "../commands.h"
    /*else */
    {   
        if (!AsmCheckCmdEnd (command_and_args))
        {
            proc_errno |= ASM_ERR_READING_CMD_NAME;
            fprintf (listing_f, "ERROR WHILE COMPILING FILE\n"
                                "ERRNO: %08X", proc_errno);\
            return proc_errno;
        }
    }

    #undef DEF_COMMAND

    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

FILE* AsmOpenFile(const char* filename, const char* mode)
{
    assert (filename);
    assert (mode);

    FILE* file = fopen(filename, mode); 

    if (!file || ferror (file) || !file || ferror (file))
    {
        proc_errno = proc_errno | ASM_FILE_OPENING_ERR;
        return NULL;
    }

    return file;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmPreprocStrArray (char** str_array, size_t num_lines)
{
    assert (str_array);

    for (size_t i = 0; i < num_lines; i++)
    {   
        for (size_t j = 0, k = 0; (str_array[i][j]) != '\0'; j++, k++)
        {   
            if (j == 0 && str_array[i][j] == ' ')
            {   
                char* tmp_ptr = str_array[i];
                printf ("B: :%s:\n", tmp_ptr);
                while (*tmp_ptr == ' ')
                {
                    ++tmp_ptr;
                }

                str_array[i] = tmp_ptr;
                printf ("A: :%s:\n", tmp_ptr);
            }

            if (str_array[i][j] == PROC_COMMENT_SYMBOL)
            {   
                str_array[i][j] = '\0';
                break;
            }
        }
    }

    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
int AsmProcessFile(const char* filename_to_read, const char* filename_to_write, const char* filename_listing)
{
    assert (filename_to_read);
    assert (filename_to_write);

    FILE* file_to_read = AsmOpenFile(filename_to_read, "r");
    FILE* file_to_write = AsmOpenFile(filename_to_write, "wb");
    FILE* file_for_listing = AsmOpenFile (filename_listing, "w");

    size_t num_symbols = CountSymbols (file_to_read);
    char* file_buffer = ReadFileToBuffer (file_to_read, num_symbols);
    size_t num_lines = CountLines (file_buffer);
    
    char** str_array = OneginFillPArray (file_buffer, num_lines, num_symbols);
    AsmPreprocStrArray (str_array, num_lines);
    
    ssize_t cmd_array_size = AsmFindCmdArraySize (str_array, num_lines);
    
    if (cmd_array_size < 0)
    {
        return proc_errno;
    }

    void* cmd_array = (void*) calloc (1, cmd_array_size);
    int program_counter = 0;
    int err_code = PROC_OK;

    for (size_t i = 0; i < num_lines; ++i)
    {   
        err_code = AsmParseCommand (cmd_array, str_array[i], &program_counter, file_for_listing);

        if (err_code != PROC_OK)
        {
            return proc_errno;
        }
    }
    
    fwrite (cmd_array, cmd_array_size, 1, file_to_write);

    fclose (file_to_read);
    fclose (file_to_write);

    free (str_array);
    free (file_buffer);
    free (cmd_array);

    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

ssize_t AsmFindCmdArraySize (char** str_array, size_t num_lines)
{   
    #define DEF_COMMAND(name, n_args, id, command_name, ...)\
        if (AsmCheckCommand (str_array[i], command_name, strlen (command_name))) \
        { \
            num_commands_bytes += sizeof (unsigned char); \
            num_args_bytes += sizeof(double) * n_args; \
        } \
        else

    size_t num_commands_bytes = 0;
    size_t num_args_bytes = 0;

    for (size_t i = 0; i < num_lines; i++)
    {
        #include "../commands.h"
        /* else */
        {   
            if (!AsmCheckCmdEnd (str_array[i]))
            {
                proc_errno |= ASM_ERR_READING_CMD_NAME;
                return -1;
            }
        }
    }

    #undef DEF_COMMAND

    return num_commands_bytes + num_args_bytes;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmPprintArgLst (FILE* file, void* val, size_t el_size)
{
    unsigned char* data_ptr = (unsigned char*) (val);

    for (size_t j = 0; j <  el_size; j++)
    {
        fprintf (file, "%02X ", data_ptr[j]);
    }

    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmUnitTest ()
{   
    AsmProcessFile ("asm_file.asm", "asm_result.asmmc", "asm.lst");
    printf ("ERRNO: %d\n", proc_errno);
    return proc_errno;
}