#include <malloc.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct namednum {
  char *name;
  int number;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

int compare_ptrs (const void* first_ptr, const void* second_ptr)
{   
    struct namednum* f_ptr = (struct namednum*) first_ptr;
    struct namednum* s_ptr = (struct namednum*) second_ptr;
    
    if (s_ptr->name == NULL || f_ptr->name == NULL)
        return 0;

    return strcmp (f_ptr->name, s_ptr->name);
}

int compare_nums (const void* first_ptr, const void* second_ptr)
{
    struct namednum* f_ptr = (struct namednum*) first_ptr;
    struct namednum* s_ptr = (struct namednum*) second_ptr;
    
    return f_ptr->number - s_ptr->number;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void fixupstrings(struct namednum *arr, size_t arrlen) 
{

    qsort (arr, arrlen, sizeof (*arr), compare_ptrs);
    char* cur_str = NULL;

    for (int i = 0; i < arrlen; i++)
    {
        if (arr[i].name == cur_str)
        {   
            char* new_str = (char*) calloc (strlen(cur_str) + 1, sizeof(*new_str));
            strcpy (new_str, cur_str);

            arr[i].name = new_str;
            continue;
        }

        cur_str = arr[i].name;
    }
    
    qsort (arr, arrlen, sizeof (*arr), compare_nums);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    size_t str_arr_len = 5;
    size_t arr_len = 10;

    char** strarray = (char**) calloc (str_arr_len, sizeof(*strarray));

    for (int i = 0; i < str_arr_len; ++i)
    {
        strarray[i] = (char*) calloc (10, sizeof(*strarray[i]));
    }

    strcpy (strarray[0], "kek");
    strcpy (strarray[1], "lol");
    strcpy (strarray[2], "arbidol");
    strcpy (strarray[3], "kurkuzeb");
    strcpy (strarray[4], "flexxxxx");

    struct namednum* array = (struct namednum*) calloc (arr_len, sizeof (*array));

    for (int i = 0; i < arr_len; i++)
    {
        array[i] = {strarray [i % str_arr_len], i};
        printf ("%d\t%p\t%s\n", i, array[i].name, array[i].name);
    }

    fixupstrings(array, arr_len);
    
    printf ("\nNEW\n");
    
    for (int i = 0; i < arr_len; i++)
    {
        printf ("%d\t%p\t%s\n", i, array[i].name, array[i].name);
    }
        
    for (int i = 0; i < arr_len; i++)
        free (array[i].name);

    free (strarray);
    free (array);

    return 0;
}