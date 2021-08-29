#include <stdio.h>
#include <stdio.h>
#include <malloc.h>
#include "onegin.h"

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

    for (i; *(string + i); i++)
    {   
        if (*(string + i) == symbol)
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

    for (i; *(string + i); i++);

    return i;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strcpy (char* destptr, const char* srcptr)
{
    assert (destptr);
    assert (srcptr);
    assert (srcptr != destptr);

    char* dest_copy = destptr;

    while (*destptr)
    {   
        *destptr = *srcptr;
        destptr++;
        srcptr++;
    }

    return dest_copy;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strncpy (char* destptr, const char* srcptr, size_t num)
{
    assert (destptr);
    assert (srcptr);
    assert (srcptr != destptr);
    assert (num != 0);

    size_t i = 1;
    char* dest_copy = destptr;
    
    while (*destptr && i < num)
    {
        *destptr = *srcptr;
        destptr++;
        srcptr++;
        i++;
    }

    return dest_copy;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strcat (char* destptr, const char* srcptr)
{
    assert (destptr);
    assert (srcptr);
    assert (srcptr != destptr);

    char* dest_copy = destptr;
    size_t index = strlen (destptr);
    size_t src_len = strlen (srcptr);

    while (*destptr)
    {
        *(destptr + index) = *srcptr;
        srcptr++;
        index++;
    }

    return dest_copy;    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strncat (char* destptr, const char* srcptr, size_t num)
{
    assert (destptr);
    assert (srcptr);
    assert (num != 0);
    assert (srcptr != destptr);

    char* dest_copy = destptr;
    size_t index = strlen (destptr);

    num += index;

    while (*destptr && index < num)
    {
        *(destptr + index) = *srcptr;
        srcptr++;
        destptr++;
        index++;       
    }

    return dest_copy;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* fgets (char* string, size_t num, FILE* filestream)
{   
    assert (string);
    assert (num != 0);
    assert (filestream);

    size_t i = 0;
    char next_char = 0;
    char* string_copy = string;

    for (i; i < num; i++)
    {
        next_char = fgetc (filestream);

        if (next_char == EOF)
        {   
            print_error ("fgets", "EOF was reached");
            return NULL;
        }

        *string = next_char;
        string++;
    }

    return string_copy;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* strdup (const char* string)
{
    assert (string);

    size_t string_len = strlen (string);
    char* new_string = NULL;
    
    new_string = calloc (string_len, 1);

    if (!new_string)
    {   
        print_error ("strdup", "Error while allocating memory");
        return NULL;
    }

    new_string = strncpy (new_string, string, string_len);

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
        *lineptr = calloc (20, 1);
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
            print_error ("getline", "EOF was reached");
            return -1;
        }

        *temp_buff = next_char;
        temp_buff++;
        total_len += 1;

        if (n - total_len < 2)
        {
            *n *= 2;
            temp_buff = realloc (temp_buff, *n);

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
