#include "onegin.h"
#include <assert.h>
#include <malloc.h>
#include <ctype.h>

void qsort (void* array, size_t n_memb,  size_t el_size,
            int (*comparator) (const void*, const void*))
{   
    assert (array);
    assert (comparator);

    unsigned pivot_index = choose_pivot (n_memb);
    unsigned left = paritation (array, n_memb, el_size, pivot_index, comparator);

    if (left > 0)
    {
        qsort (array, left, el_size, comparator);
    }

    if (n_memb - left - 1 > 0)
    {
        qsort (array + (left + 1) * el_size, n_memb - left - 1, el_size, comparator);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned paritation (void* array, size_t n_memb, size_t el_size, unsigned pivot_index, 
                     int (*comparator) (const void*, const void*))
{   
    assert (array);
    assert (comparator);

    void* pivot = array + pivot_index * el_size;
    unsigned i = 1;
    unsigned left = 0;

    if (n_memb <= 1)
    {
        return left;
    }

    swap (array, pivot, el_size);
    pivot = array;

    for (i; i < n_memb; i++)
    {
        if (comparator (array + i * el_size, pivot) > 0)
        {   
            left++;
            swap (array + left * el_size, array + i * el_size, el_size);
        }
    }

    swap (pivot, array + left * el_size, el_size);

    return left;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void swap (void* a, void* b, size_t el_size)
{   
    assert (a);
    assert (b);
    
    char* a_arr = (char*) a;
    char* b_arr = (char*) b;
    char tmp = 0;
    unsigned i = 0;

    for (i; i < el_size; i++)
    {
        tmp = a_arr[i];
        a_arr[i] = b_arr[i];
        b_arr[i] = tmp;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned choose_pivot (size_t n_memb)
{
    return n_memb / 2;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int lexicographic_comparator (const void* string_1, const void* string_2)
{   
    assert (string_1);
    assert (string_2);

    string* str_1 = (string*) string_1;
    string* str_2 = (string*) string_2;

    unsigned minlen = (str_1->len < str_2->len)? str_1->len:str_2->len;
    unsigned i = 0;

    for (i; i < minlen; i++)
    {   
        if (!isalpha (str_1->start[i]) || !isalpha (str_2->start[i]))
        {
            continue;
        }

        if (str_1->start[i] != str_2->start[i])
        {
            return (int) str_1->start[i] - (int) str_2->start[i];
        }
    }
    
    if (str_1->len == str_2->len)
    {
        return 0;
    }

    return (str_1->len < str_2->len)? 1:-1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int string_ctor (string* string, char* data, size_t len)
{   
    assert (string);
    assert (data);

    string->start = data;
    string->len = len;

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int count_symbols (const char* filename)
{
    FILE* file = fopen (filename, "r");

    if (!file || ferror (file))
    {
        print_error ("count_symbols", "Error while opening file");
        return -1;
    }

    fseek (file, 0, SEEK_END);
    int num_sumbols = ftell (file);
    fseek (file, 0, SEEK_SET);

    if (fclose (file) != 0)
    {
        print_error ("count_symbols", "Error while closing file");
        return -1;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int read_file_to_buffer (const char* filename, char* buffer, int num_symbols)
{   
    assert (num_symbols > 0);
    assert (filename);
    assert (buffer);

    FILE* file = fopen (filename, "r");

    if (!file || ferror (file))
    {
        print_error ("read_file_to_buffer", "Error while opening file");
        return -1;
    }

    int actual_num_symbols = fread (buffer, sizeof (char), num_symbols, file);

    // TODO Андрей, а такая проверка покатит? 
    // В смысле, я не понял, учитывает ли fread \0, потому что если я верно понял, 
    // то count_symbols учитывает \0 в подсчете символов.
    if (actual_num_symbols != num_symbols)
    {
        print_error ("read_file_to_buffer", "Error while reading file");
        return -1;
    }
    
    if (fclose (file) != 0)
    {
        print_error ("read_file_to_buffer", "Error while closing file");
        return -1;
    }

    return 0;
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

int fill_array (char* buffer, string** array, unsigned line_num, unsigned num_symbols)
{   
    assert (buffer);
    assert (array);

    int line_len = 0;
    int j = 0;
    char* line_ptr = buffer;

    for (int i = 0; i < line_num; i++)
    {
        while (line_ptr[j] != '\n' && line_len < num_symbols)
        {   
            j++;
            line_len++;
        }

         if (line_ptr[j] == '\n')
            line_ptr[j] = '\0';

        string str;
        string_ctor (&str, line_ptr, line_len);
        array[i] = &str;

        line_ptr += j;
        j = 0;
        line_len = 0;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int save_to_file (string** array, const char* filename, unsigned line_num)
{
    FILE* file = fopen (filename, "w");

    if (!file || ferror (file))
    {
        print_error ("save_to_file", "Error while opening file");
        return NULL;
    }

    for (unsigned i = 0; i < line_num; i++)
    {   
        fputs (array[i]->start, file);
        fputc ('\n', file);
    }

    if (fclose (file) != 0)
    {
        print_error ("read_file_to_buffer", "Error while closing file");
        return -1;
    }

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

    fprintf (stderr, "File: %s\n"
                     "Line: %d\n"
                     "Current function: %s()\n"
                     "Failed function: %s()\n"
                     "Error message: %s\n",
                    file, line, current_function, failed_function, error_text);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
