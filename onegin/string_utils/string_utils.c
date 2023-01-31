#include <stdio.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "string_utils.h"

int puts (const char* string)
{   
    assert (string);

    int i = 0;

    for (i; string[i]; i++)
    {
        if (putchar (string[i]) == EOF)
        {   
            print_error ("puts", "Error while printing symbol");
            return -1;
        }
    }
        
    if (putchar ("/n") == EOF)
    {   
        print_error ("puts", "Error while printing symbol");
        return -1;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strchr (char* string, int symbol)
{
    assert (string);

    int i = 0;

    for (i; string[i] != '\0'; i++)
    {   
        if (string[i] == symbol)
        {
            return string + i;
        }
    }

    return NULL;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

size_t strlen (char* string)
{   
    assert (string);

    size_t i = 0;

    for (i; string[i] != '\0'; i++);

    return i;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strcpy (char* destptr, const char* srcptr)
{
    assert (destptr);
    assert (srcptr);
    assert (srcptr != destptr);

    size_t i = 0;
    
    while (srcptr[i] != '\0')
    {   
        destptr[i] = srcptr[i];
        i++;
    }

    destptr[i] = '\0';

    return destptr;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strncpy (char* destptr, const char* srcptr, size_t num)
{
    assert (destptr);
    assert (srcptr);
    assert (srcptr != destptr);
    assert (num != 0);

    size_t i = 0;
    
    while (i < num && srcptr[i] != '\0')
    {   
        destptr[i] = srcptr[i];
        i++;
    }

    destptr[i] = '\0';

    return destptr;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strcat (char* destptr, const char* srcptr)
{
    assert (destptr);
    assert (srcptr);
    assert (srcptr != destptr);

    size_t index = strlen (destptr);

    while (*srcptr != '\0')
    {
        destptr[index] = *srcptr;
        srcptr++;
        index++;
    }

    return destptr;    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strncat (char* destptr, const char* srcptr, size_t num)
{
    assert (destptr);
    assert (srcptr);
    assert (num != 0);
    assert (srcptr != destptr);

    size_t index = strlen (destptr);

    num += index;

    while (*srcptr != '\0' && index < num)
    {
        destptr[index] = *srcptr;
        srcptr++;
        index++;       
    }

    return destptr;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* fgets (char* string, size_t num, FILE* filestream)
{   
    assert (string);
    assert (num != 0);
    assert (filestream);

    size_t i = 0;
    char next_char = 0;

    for (i; i < num; i++)
    {
        next_char = fgetc (filestream);

        if (next_char == EOF)
        {   
            print_error ("fgets", "EOF was reached");
            return NULL;
        }

        string[i] = next_char;
    }

    return string;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strdup (const char* string)
{
    assert (string);

    size_t full_string_len = strlen (string) + 1;
    char* new_string = NULL;
    
    new_string = (char*) calloc (full_string_len, 1);

    if (!new_string)
    {   
        print_error ("strdup", "Error while allocating memory");
        return NULL;
    }

    new_string = strncpy (new_string, string, full_string_len);

    return new_string;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int getline (char** lineptr, size_t* n, FILE* stream)
{
    assert (lineptr);
    assert (n);
    assert (stream);

    if (!(*lineptr) && !(*n))
    {
        *lineptr = (char*) calloc (20, 1);
        *n = 20;

        if (!(*lineptr))
        {   
            print_error ("getline", "Error while allocating memory");
            return -1;
        }
    }

    char* temp_buff = *lineptr;
    char next_char = 0;
    size_t total_len = 0;

    while (next_char != '\n')
    {
        next_char = fgetc (stream);

        if (next_char == EOF)
        {   
            return -1;
        }

        *temp_buff = next_char;
        temp_buff++;
        total_len += 1;

        if (n - total_len < 2)
        {
            *n *= 2;
            temp_buff = (char*) realloc (temp_buff, *n);

            if (!temp_buff)
            {
                print_error ("getline", "Error while re-allocating memory");
                return -1;
            }
        }
    }

    lineptr = &temp_buff;
    n = &total_len;

    return total_len;
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

    fprintf (stderr, "File: %s\n"
                     "Line: %d\n"
                     "Current function: %s()\n"
                     "Failed function: %s()\n"
                     "Error message: %s\n",
                    file, line, current_function, failed_function, error_text);
}
