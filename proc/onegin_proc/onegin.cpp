#include "../machine/proc.h"
#include "onegin.h"
#include <assert.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StringCtor (String* string, char* data, size_t len)
{   
    assert (data);

    string->start = data;
    string->len = len;

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CountSymbols (FILE* file)
{   
    assert (file);
    
    fseek (file, 0, SEEK_END);
    int num_sumbols = ftell (file);
    fseek (file, 0, SEEK_SET);

    return num_sumbols;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* ReadFileToBuffer (FILE* file, int num_symbols)
{   
    assert (num_symbols > 0);
    assert (file);

    char* file_buffer = (char*) calloc (num_symbols + 1, sizeof (char));
    
    CHECK_POINTER (file_buffer, "ReadFileToBuffer", NULL);

    int actual_num_symbols = fread (file_buffer, sizeof (char), num_symbols, file);

    if (actual_num_symbols != num_symbols)
    {
        OneginErrno ("ReadFileToBuffe", "Error while reading file");
        return NULL;
    }

    return file_buffer;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CountLines (char* buffer)
{   
    assert (buffer);

    char c = buffer[0];
    char last_c = c;

    int num_lines = 0;

    for (int i=0; (c = buffer[i]) != '\0'; i++)
    {
        if (c == '\n')
        {
            ++num_lines;
        }

        last_c = c;
    }
    
    if (last_c != '\n')
        ++num_lines;

    return num_lines;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int OneginFillPArray
 (char* buffer, String** ptr_array, String* str_array, 
                unsigned line_num, unsigned num_symbols)
{   
    assert (buffer);
    assert (ptr_array);
    assert (str_array);
    assert (num_symbols > 0);

    unsigned line_len = 0;
    unsigned line_iter = 0;
    char* line_ptr = buffer;

    for (unsigned i = 0; i < line_num; i++)
    {   
        line_ptr = buffer + line_iter;
        line_len = 0;

        while (buffer[line_iter] != '\n' && line_iter < num_symbols)
        {   
            line_iter++;
            line_len++;
        }

        if (buffer[line_iter] == '\n' || buffer[line_iter] == PROC_COMMENT_SYMBOL)
            buffer[line_iter] = '\0';

        line_len++;
        line_iter++;

        String str;
        StringCtor (&str, line_ptr, line_len);

        str_array[i] = str;
        ptr_array[i] = &str_array[i];
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int OneginSavePArrToFile (String** array, FILE* file, unsigned line_num)
{   
    assert (array);
    assert (file);

    fputs ("\n\n\n"
           "===============================\n"
           "\t\tFILE STARTS HERE\n"
           "===============================\n", file);

    for (unsigned i = 0; i < line_num; i++)
    {   
        if (array[i]->len > 2)
        {
            fputs (array[i]->start, file);
            fputc ('\n',  file);
        }
    }

    fputs ("=============================\n"
           "\t\tFILE ENDS HERE\n"
           "=============================\n\n\n", file);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int OneginSaveOrigToFile (String* array, FILE* file, unsigned line_num)
{   
    assert (array);
    assert (file);

    fputs ("\n\n\n"
           "=================================\n"
           "\tORIGINAL TEXT STARTS HERE\n"
           "=================================\n", file);

    for (unsigned i = 0; i < line_num; i++)
    {   
            fputs (array[i].start, file);
            fputc ('\n',  file);
    }

    fputs ("=================================\n"
           "\tORIGINAL TEXT  ENDS HERE\n"
           "=================================\n\n\n", file);

    return 0;
}
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void OneginErrnoFunc (const char* file, const int line, const char* current_function, 
                       const char* failed_function, const char* error_text)
{   
    assert (file);
    assert (line);
    assert (current_function);
    assert (failed_function);
    assert (error_text);

    FILE* log_file = fopen ("onegin.log", "wa+");
    
    if (!log_file || ferror(log_file))
    {
        log_file = stderr;
    }

    fprintf (log_file, "File: %s\n"
                       "Line: %d\n"
                       "Current function: %s()\n"
                       "Failed function: %s()\n"
                       "Error message: %s\n",
                    file, line, current_function, failed_function, error_text);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
