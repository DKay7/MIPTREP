#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    long long int denum;
    long long int fract;
} Fract;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int comp (const void* a, const void* b)
{   
    const Fract* a_ = (const Fract*) a;
    const Fract* b_ = (const Fract*) b;

    long long int diff = a_->denum * b_->fract - b_->denum * a_->fract;

    if (diff > 0)
    {
        return 1;
    }

    else if (diff < 0)
    {
        return -1;
    }

    else // (diff == 0)
    {   
        diff = a_->denum - b_->denum;

        if (diff > 0)
        {
            return 1;
        }
        else if (diff < 0)
        {
            return -1;
        } 

        return 0;
    }


}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


int main()
{
    Fract* array = (Fract*) calloc (10000, sizeof (*array));
    int num = 0;

    scanf ("%d", &num);
    for (int i = 0; i < num; i++)
    {   
        scanf("%lld/%lld", &(array[i].denum), &(array[i].fract));
    }

    qsort (array, num, sizeof(Fract), comp);
    
    for (int i = 0; i < num; i++)
    {
        printf("%lld/%lld\n", array[i].denum, array[i].fract);
    }

    printf("\n");

    free (array);

    return 0;
}