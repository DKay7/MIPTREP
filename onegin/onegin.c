#include <onegin.h>
#include <assert.h>

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
    string* str_1 = (string*) string_1;
    string* str_2 = (string*) string_2;

    unsigned minlen = (str_1->len < str_2->len)? str_1->len:str_2->len;
    unsigned i = 0;

    for (i; i < minlen; i ++)
    {
        if (str_1->start[i] != str_2->start[i])
        {
            break;
        }
    }

    return (int) str_1->start[i] - (int) str_2->start[i];
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
