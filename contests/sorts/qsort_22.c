#include <stdlib.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int comp (const void* a, const void* b)
{   char ac = *((const char*) a);
    char bc = *((const char*) b);
    
    return ac - bc;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


int main()
{
    char array[1000];
    char c = 0;
    int i = 0;
    int num = 0;

    while ((c = getchar ()) != '.')
    {
        array[i] = c;
        i ++;
    }

    num = i;

    qsort (array, num, sizeof(char), comp);
    
    for (i = 0; i < num; i++)
    {
        printf("%c", array[i]);
    }
    
    printf (".");

    return 0;
}