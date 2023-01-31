#include <stdlib.h>
#include <stdio.h>

#define ll long long unsigned

#define MAX(a, b) ({           \
        __typeof__(a) __a = a; \
        __typeof__(b) __b = b; \
        __a > __b ? __a : __b; \
})

int safe_get(int* x, int n, int i, int otherwise) {
    return i >= 0 && i < n ? x[i] : otherwise;
}

void getlen (int* a, int* len)
{
    for (int i=0; i < (*len); i++)
    {
        if (a[i] != 0)
        {
            return;
        }
        (*len)--;
    }
}

void SubLong (int* a, int* b, int a_n, int b_n)
{
 for (int a_i = a_n - 1, b_i = b_n - 1; a_i >= 0 || b_i >= 0; -- a_i, -- b_i) {
        int a_num = safe_get(a, a_n, a_i, /* default */ 0);
        int b_num = safe_get(b, b_n, b_i, /* default */ 0);

        // *** *** unsafe if a < b *** ***
        a[a_i] = (a_num >= b_num ? 0 : 10) + (a_num - b_num);

        if (a_num < b_num)
            for (int ind = a_i - 1; ind >= 0; -- ind) {
                if (a[ind] > 0) {
                    -- a[ind];
                    break;
                } else a[ind] = 9;
            }
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ComapreLong (int *a, int* b, int len_a, int len_b)
{   
    getlen (a, &len_a);
    getlen (b, &len_b);

    if (len_a != len_b)
    {
        return len_a - len_b;
    }
    
    for (int i = 0; i < len_a; i ++)
    {
        if (a[i] != b[i])
        {
            return a[i] - b[i];
        }
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int* GcdLong (int* a, int* b, int len_a, int len_b)
{
    while (ComapreLong (a, b, len_a, len_b) != 0)
    {
        if (ComapreLong (a, b, len_a, len_b) > 0)
        {
            SubLong (a, b, len_a, len_b);
            printf ("ii\n");
            getlen (a, &len_a);
            getlen (b, &len_b);

        }
        else
        {
            SubLong (b, a, len_b, len_a);
            getlen (a, &len_a);
            getlen (b, &len_b);
            printf ("i\n");
        }
    }

    return a;
}

int main ()
{   
    int a[100];
    int b[100];
 
    int a_len = 0; scanf ("%d", &a_len);

    for (int i = 0; i < a_len; ++ i)
        scanf("%d", a + i);

    int b_len = 0; scanf ("%d", &b_len);

    for (int i = 0; i < b_len; ++ i)
        scanf("%d", b + i);

    GcdLong (a, b, a_len, b_len);

    for (int j = 0; j < a_len; j ++)
    {
        printf ("%d ", a[j]);
    }

    return 0;

}