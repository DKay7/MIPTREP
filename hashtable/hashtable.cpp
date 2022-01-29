#include "hashtable.h"
#include <stdio.h>
#include "default_hash_funtions.h"

void data_printer (FILE* file, HT_Pair<char*, int>* data_)
{
    fprintf (file, "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">"
                   "<tr><td>KEY:</td><td>%s</td></tr>"
                   "<tr><td>VALUE:</td><td>%d [%c]</td></tr></table>", 
                   data_->key, data_->value, 'A' - 1 +data_->value);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// uint64_t int_hash (int value)
// {
//     return (uint64_t) abs (value) % 5;
// }

bool key_equality (char* first, char* second)
{   
    return (strcmp (first, second) == 0);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    HashTable<char*, int> ht = {};
    HashTableCtor<char*, int> (&ht, 2, str_hash, key_equality);

    const int size = 15;
    int vals[size] = {};
    char keys[size][5 * size] = {};

    for (int i = 0; i < size; i++)
    {   
        vals[i] = 1 + i;
        sprintf (keys[i], "square of %d is %d", vals[i], vals[i] * vals[i]);

        printf ("insert %c: %d\n", 'A' + i, HashTableInsert (&ht, keys[i], vals[i]));

    }
    
    HashTableDump (&ht, data_printer);
    printf ("SIZE: %d\n", ht.values->size);
    // HashTableDump (&ht, data_printer);

       for (int i = 0; i < size; i++)
    {   
        printf ("Delete %c: %d\n", 'A' + i, HashTableDelete (&ht, keys[i]));
    }

    // printf ("Delete B: %d\n", HashTableDelete (&ht, vals[2]));
    printf ("SIZE: %d\n", ht.values->size);
    HashTableDump (&ht, data_printer);

    HashTableDtor (&ht);
    return 0;
}