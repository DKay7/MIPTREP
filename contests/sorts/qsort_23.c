#include <stdlib.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int comp (const void* a, const void* b)
{
    int a_ = *((const int*) a);
    int b_ = *((const int*) b);

    while (a_ > 0 && b_ > 0)
    {
        int digit_a = a_ % 10;
        int digit_b = b_ % 10;

        if (digit_a != digit_b)
        {   
            return digit_a - digit_b;
        }

        a_ /= 10;
        b_ /= 10;
    }

    return a_ - b_;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    int array[1002];
    int num = 0;

    scanf ("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d", array + i);
    }

    qsort (array, num, sizeof(int), comp);
    
    for (int i = 0; i < num; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
    return 0;
}