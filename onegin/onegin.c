#include "onegin.h"
#include <assert.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int string_ctor (string* string, char* data, size_t len)
{   
    assert (data);

    string->start = data;
    string->len = len;

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int count_symbols (FILE* file)
{   
    assert (file);
    
    fseek (file, 0, SEEK_END);
    int num_sumbols = ftell (file);
    fseek (file, 0, SEEK_SET);

    return num_sumbols;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* read_file_to_buffer (FILE* file, int num_symbols)
{   
    assert (num_symbols > 0);
    assert (file);

    char* file_buffer = (char*) calloc (num_symbols + 1, sizeof (char));
    
    CHECK_POINTER (file_buffer, "read_file_to_buffer", NULL);

    int actual_num_symbols = fread (file_buffer, sizeof (char), num_symbols, file);

    if (actual_num_symbols != num_symbols)
    {
        print_error ("read_file_to_buffer", "Error while reading file");
        return NULL;
    }

    return file_buffer;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int count_lines (char* buffer)
{   
    assert (buffer);

    char c = buffer[0];
    int num_lines = 0;

    for (int i=0; (c = buffer[i]) != '\0'; i++)
    {
        if (c == '\n')
        {
            num_lines++;
        }
    }
    
    return num_lines;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int fill_array (char* buffer, string** ptr_array, string* str_array, 
                unsigned line_num, unsigned num_symbols)
{   
    assert (buffer);
    assert (ptr_array);
    assert (str_array);
    assert (num_symbols > 0);

    unsigned line_len = 0;
    int line_iter = 0;
    char* line_ptr = buffer;

    for (unsigned i = 0; i < line_num; i++)
    {
        while (line_ptr[line_iter] != '\n' && line_len < num_symbols)
        {   
            line_iter++;
            line_len++;
        }

        line_len++;
        line_iter++;

        if (line_ptr[line_len - 2] != '\n')
            line_ptr[line_len - 2] = '\n';
        
        line_ptr[line_len - 1] = '\0';

        string str;
        string_ctor (&str, line_ptr, line_len);

        str_array[i] = str;
        ptr_array[i] = &str_array[i];

        line_ptr += line_iter;
        line_iter = 0;
        line_len = 0;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int save_to_file (string** array, FILE* file, unsigned line_num)
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

int save_original_to_file (string* array, FILE* file, unsigned line_num)
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

void print_error_func (const char* file, const int line, const char* current_function, 
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
