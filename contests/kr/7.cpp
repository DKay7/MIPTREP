#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
    int data[10000];
    int len;
} LongD;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ComapreLong (const void* a_, const void* b_)
{   
    LongD* a = (LongD*) a_;
    LongD* b = (LongD*) b_;

    if (a->len != b->len)
    {
        return a->len - b->len;
    }
    
    int min_len = (a->len < b->len)? a->len : b->len;
    for (int i = 0; i < min_len; i ++)
    {
        if (a->data[i] != b->data[i])
        {
            return a->data[i] - b->data[i];
        }
    }

    return 0;
}

int main ()
{
    int n = 0;
    scanf ("%d", &n);
    LongD* arr = (LongD*) calloc (n, sizeof (LongD));

    for (int i = 0; i < n; i ++)
    {   
        int m = 0;
        scanf ("%d", &m);
        for (int j = 0; j < m; j ++)
        {
            scanf ("%d", &arr[i].data[j]);
        }
        arr[i].len = m;
    }

    qsort (arr, n, sizeof (LongD), ComapreLong);

    for (int i = 0; i < n; i ++)
    {   
        printf ("%d ", arr[i].len);

        for (int j = 0; j < arr[i].len; j ++)
        {
            printf ("%d ", arr[i].data[j]);
        }

        printf ("\n");
    }

    free (arr);
}
