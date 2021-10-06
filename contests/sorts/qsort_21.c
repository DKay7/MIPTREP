#include <stdlib.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int comp (const void* a, const void* b)
{   double ad = *((const double*) a);
    double bd = *((const double*) b);
    
    if (ad > bd)
    {
        return 1;
    }
    else if (ad < bd)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


int main()
{
    double array[1000];
    int num = 0;

    scanf ("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%lf", array + i);
    }

    qsort (array, num, sizeof(double), comp);
    
    for (int i = 0; i < num; i++)
    {
        printf("%.2lf ", array[i]);
    }
    
    printf ("\n");

    return 0;
}