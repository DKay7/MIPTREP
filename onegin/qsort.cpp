#include "qsort.h"
#include "onegin.h"
#include <assert.h>
#include <ctype.h>

void qsort (void* array, size_t n_memb,  size_t el_size,
            int (*comparator) (const void*, const void*))
{   
    assert (array);
    assert (comparator);

    if (n_memb <= 0)
    {
        return;
    }

    char* array_pointer = (char*) array;
    
    unsigned pivot_index = choose_pivot (n_memb);
    unsigned left = paritation (array_pointer, n_memb, el_size, pivot_index, comparator);

    if (left > 0)
    {
        qsort (array_pointer, left, el_size, comparator);
    }

    if (n_memb - left - 1 > 0)
    {
        qsort (array_pointer + (left + 1) * el_size, n_memb - left - 1, el_size, comparator);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned paritation (char* array, size_t n_memb, size_t el_size, unsigned pivot_index, 
                     int (*comparator) (const void*, const void*))
{   
    assert (array);
    assert (comparator);

    void* pivot = array + pivot_index * el_size;
    unsigned left = 0;

    swap (array, pivot, el_size);
    pivot = array;

    for (unsigned i = 1; i < n_memb; i++)
    {   
        if (comparator (array + i * el_size, pivot) < 0)
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

    for (unsigned i = 0; i < el_size; i++)
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

int compare_letters (char a, char b)
{
    a = tolower (a);
    b = tolower (b);

    if (a != b)
    {
        return (a > b)? 1 : -1;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int lexicographic_comparator (const void* string_1, const void* string_2)
{   
    assert (string_1);
    assert (string_2);

    String* str_1 = *((String**) string_1);
    String* str_2 = *((String**) string_2);

    unsigned i = 0;
    unsigned j = 0;

    while (i < str_1->len && j < str_2->len)
    {   
        if (isalpha (str_1->start[i]) && isalpha (str_2->start[j]) &&
            tolower (str_1->start[i]) != tolower (str_2->start[j]))
        {   
            return compare_letters (str_1->start[i], str_2->start[j]);
        }

        else if (!isalpha (str_1->start[i]) && isalpha (str_2->start[j]))
        {   
            i++;
        }

        else if (isalpha (str_1->start[i]) && !isalpha (str_2->start[j]))
        {
            j++;
        }

        else
        {
            i++;
            j++;
        }
    }
    
    if (str_1->len == str_2->len)
    {   
        return 0;
    }

    return (str_1->len > str_2->len)? 1 : -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int reversed_lexicographic_comparator (const void* string_1, const void* string_2)
{   
    assert (string_1);
    assert (string_2);

    String* str_1 = *((String**) string_1);
    String* str_2 = *((String**) string_2);

    int i = str_1->len - 1;
    int j = str_2->len - 1;

    while (i >= 0 && j >= 0)
    {   
        if (isalpha (str_1->start[i]) && isalpha (str_2->start[j]) &&
            tolower (str_1->start[i]) != tolower (str_2->start[j]))
        {   
            return compare_letters (str_1->start[i], str_2->start[j]);
        }

        else if (!isalpha (str_1->start[i]) && isalpha (str_2->start[j]))
        {   
            i--;
        }

        else if (isalpha (str_1->start[i]) && !isalpha (str_2->start[j]))
        {
            j--;
        }

        else
        {
            i--;
            j--;
        }
    }
    
    if (str_1->len == str_2->len)
    {   
        return 0;
    }

    return (str_1->len < str_2->len)? 1 : -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
