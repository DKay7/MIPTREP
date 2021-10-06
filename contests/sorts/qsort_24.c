#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int comp (const void* a, const void* b)
{
    int a_ = *((const int*) a);
    int b_ = *((const int*) b);

    return a_ - b_;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    int array_orig[1002];
    int array_sorted[1002];
    int j = 0;
    int num = 0;

    memset (array_orig, 0, 1002 * sizeof (int));
    memset (array_sorted, 0, 1002 * sizeof (int));

    for (int i = 0; i < num; i++)
    {
        array_orig[i] = 0;
        array_sorted[i] = 0;
    }

    scanf ("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d", array_orig + i);
        array_sorted[i] = array_orig[i];
    }

    qsort (array_sorted, num, sizeof(int), comp);
    
    for (int i = 0; i < num; i++)
    {   
        if(array_orig[i] % 2 != 0)
        {
            printf("%d ", array_orig[i]);
        }
        else
        {
            while (array_sorted[j]  % 2 != 0)
            {
                j++;
            }

            printf("%d ", array_sorted[j]);
            j++;
        }
    }

    printf("\n");
    return 0;
}
