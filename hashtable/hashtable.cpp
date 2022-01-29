#include "hashtable.h"
#include <stdio.h>

void data_printer (FILE* file, HT_Pair<int, char*>* data_)
{
    fprintf (file, "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">"
                   "<tr><td>KEY:</td><td>%d [%c]</td></tr>"
                   "<tr><td>VALUE:</td><td>%s</td></tr></table>", 
                   data_->key, 'A' - 1 +data_->key, data_->value);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t int_hash (int value)
{
    return (uint64_t) abs (value) % 5;
}

bool key_equality (int* first, int* second)
{   
    return (*first) == (*second);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    HashTable<int, char*> ht = {};
    HashTableCtor<int, char*> (&ht, 2, int_hash, key_equality);

    const int size = 5;
    int keys[size] = {};
    char vals[size][5 * size] = {};

    for (int i = 0; i < size; i++)
    {   
        keys[i] = 1 + i % 3;
        sprintf (vals[i], "square of %d is %d", keys[i], keys[i] * keys[i]);

        printf ("insert %c: %d\n", 'A' + i, HashTableInsert (&ht, keys[i], vals[i]));

    }
    
    HashTableDump (&ht, data_printer);
    printf ("SIZE: %d\n", ht.values->size);
    // HashTableDump (&ht, data_printer);

       for (int i = 0; i < size; i++)
    {   
        printf ("Delete %c: %d\n", 'A' + i, HashTableDelete (&ht, keys[i]));
    }

    // printf ("Delete B: %d\n", HashTableDelete (&ht, keys[2]));
    printf ("SIZE: %d\n", ht.values->size);
    HashTableDump (&ht, data_printer);

    HashTableDtor (&ht);
    return 0;
}