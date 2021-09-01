#include "onegin.h"
#include "string_utils/string_utils.h"
#include <assert.h>
#include <malloc.h>

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

    if (n_memb <= 1)
    {
        return;
    }

    void* pivot = array + pivot_index * el_size;
    unsigned i = 1;
    unsigned left = 0;

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

string* string_ctor (char* str_data, size_t len)
{   
    assert (str_data);

    string str = {str_data, len};

    return &str;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned count_lines (FILE* file)
{   
    assert (file);

    char* linebuff = NULL;
    size_t n = 0;
    unsigned line_cnt = 0;

    while (getline (&linebuff, &n, file) != EOF)
    {
        line_cnt++;
    }

    return line_cnt;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

string** parse_file_to_array (char* filename, unsigned line_num)
{
    FILE* file = fopen (filename, 'r');

    if (!file || ferror (file))
    {
        print_error ("parse_file_to_array", "Error while opening file");
        return NULL;
    }

    string** array = (string**) calloc (line_num, sizeof (string*));

    if (!array)
    {
        print_error ("parse_file_to_array", "Error while allocated memory");
        return NULL;
    }

    char* linebuff = NULL;
    size_t str_len = 0;
    unsigned i = 0;

    for (i; i < line_num; i++)
    {   
        getline (&linebuff, &str_len, file);
        array[i] = string_ctor (linebuff, str_len);

        linebuff = NULL;
        str_len = 0;
    }

    fclose (file);

    return array;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void save_to_file (string** array, char* filename, unsigned line_num)
{
    FILE* file = fopen (filename, 'w');

    if (!file || ferror (file))
    {
        print_error ("parse_file_to_array", "Error while opening file");
        return NULL;
    }

    unsigned i = 0;
    for (i; i < line_num; i++)
    {   
        fputs (array[i]->start, file);
    }

    fclose (file);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
