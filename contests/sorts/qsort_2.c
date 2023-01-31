#include <stdlib.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int comp (const void* a, const void* b)
{
    return *((const int*) a) - *((const int*) b);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


int main()
{
    int array[1000];
    int num = 0;

    scanf ("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d", array + i);
    }

    qsort (array, num, sizeof(int), comp);
    
    for (int i =0; i<num; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
    return 0;
}