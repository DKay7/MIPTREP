#include "hashtable.h"
#include <stdio.h>
#include "default_hash_functions.h"

void data_printer (FILE* file, HT_Pair<char*, int>* data_)
{   
    fprintf (file, "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">"
                   "<tr><td>KEY:</td><td>%s</td></tr>"
                   "<tr><td>VALUE:</td><td>%d [%c]</td></tr></table>", 
                   data_->key, data_->value, 'A' - 1 +data_->value);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool key_equality (char* first, char* second)
{   
    return (strcmp (first, second) == 0);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    HashTable<char*, int> ht = {};
    HashTableCtor<char*, int> (&ht, 2, str_hash, key_equality);

    const int size = 7;
    int vals[size] = {};
    char keys[size][5 * size] = {};

    for (int i = 0; i < size; i++)
    {   
        vals[i] = 1 + i;
        sprintf (keys[i], "square of %d is %d", vals[i], vals[i] * vals[i]);

        printf ("insert %c: %d\n", 'A' + i, HashTableInsert (&ht, keys[i], vals[i]));
        printf ("INDEX OF %s IS %lu\n", keys[i], HashTableFind (&ht, keys[i]));
        // HashTableDump (&ht, data_printer, true);

    }
    
    HashTableDump (&ht, data_printer);
    printf ("SIZE: %d; CAP: %lu\n", ht.values->size, ht.buckets_capacity);

    for (int i = 0; i < size; i++)
    {   

        printf ("INDEX OF %s IS %lu\n", keys[i], HashTableFind (&ht, keys[i]));
    }

    for (int i = 0; i < size; i++)
    {   
        printf ("Delete %c: %d\n", 'A' + i, HashTableDelete (&ht, keys[i]));
    }

    printf ("SIZE: %d; CAP: %lu\n", ht.values->size, ht.buckets_capacity);

    HashTableDtor (&ht);
    return 0;
}