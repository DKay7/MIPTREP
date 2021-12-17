#include <stdio.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n = 0;
    int m = 0;
    int i_node, j_node;
    scanf ("%d %d", &n, &m);

    int** a =  (int**) calloc (n, sizeof (*a));

    for (int i = 0; i < n; i++) {
        a[i] = (int*) calloc (n, sizeof (*a[i]));
    }
    
    for (int i = 0; i < m; i++)
    {
        scanf ("%d %d", &i_node, &j_node);
        a[j_node][i_node] = 1;
        a[i_node][j_node] = 1;
    }
    

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf ("%d ", a[i][j]);
        }

        printf ("\n");
    }

    for (int i = 0; i < n; i++) {
        free (a[i]);
    }

    free (a);
    return 0;
}