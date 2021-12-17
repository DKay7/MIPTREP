#include <stdio.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n = 0;
    int num_roads = 0;
    scanf ("%d", &n);

    int** a =  (int**) calloc (n, sizeof (*a));

    for (int i = 0; i < n; i++) {
        a[i] = (int*) calloc (n, sizeof (*a[i]));

        for (int j = 0; j < n; j++) {
            scanf ("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i < j && a[i][j] == 1)
            {
                num_roads += 1;
            }
        }
    }

    printf ("%d\n", num_roads);

    for (int i = 0; i < n; i++) {
        free (a[i]);
    }

    free (a);
    return 0;
}