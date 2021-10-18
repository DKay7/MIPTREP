#include "onegin.h"
#include <assert.h>
#include <malloc.h>

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

char** OneginFillPArray (char* buffer, unsigned line_num, unsigned num_symbols)
{   
    assert (buffer);

    unsigned line_iter = 0;
    char* line_ptr = buffer;

    char** str_array = (char**) calloc (line_num, sizeof (char*));

    if (!str_array)
    {
        return NULL;
    }

    for (unsigned i = 0; i < line_num; i++)
    {   
        line_ptr = buffer + line_iter;

        while (buffer[line_iter] != '\n' && line_iter < num_symbols)
        {   
            line_iter++;
        }

        if (buffer[line_iter] == '\n')
            buffer[line_iter] = '\0';

        line_iter++;

        str_array[i] = line_ptr;
    }

    return str_array;
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
