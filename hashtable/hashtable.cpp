#include "hashtable.h"
#include <stdio.h>

void data_printer (FILE* file, int* a)
{
    fprintf (file, "%d", *a);
}

int main ()
{
    HashTable<int> hs = {};
    int a = 42;
    int b = 234;
    int c = 42;

    HashTableCtor (&hs, 10, DefaultHashFunction<int>);
    printf ("%d\n", hs.list->size);

    printf ("A: %d\n", HashTableInsert (&hs, a));
    printf ("B: %d\n", HashTableInsert (&hs, b));
    printf ("C: %d\n", HashTableInsert (&hs, c));
    // LLDump(hs.list, data_printer);
    HashTableDump (&hs, data_printer);

    HashTableDtor (&hs);
    return 0;
}