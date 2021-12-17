#include <stdio.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    int row1, row2, col1, col2;
    double **a, **b, **c;

    scanf ("%d %d %d %d", &row1, &col1, &row2, &col2);

    if (col1 != row2) {
        printf ("-1");
        return 0;
    }

    // Ввод элементов первой матрицы
    a =  (double**) calloc (row1, sizeof (*a));

    for (int i = 0; i < row1; i++) {
        a[i] = (double*) calloc (col1, sizeof (*a[i]));

        for (int j = 0; j < col1; j++) {
            scanf ("%lg", &a[i][j]);
        }
    }

    // Ввод элементов второй матрицы
    b =  (double**) calloc (row2, sizeof (*b));

    for (int i = 0; i < row2; i++) {
        b[i] = (double*) calloc (col2, sizeof (*b[i]));

        for (int j = 0; j < col2; j++) {
            scanf ("%lg", &b[i][j]);
        }
    }

    // Умножение матриц
    c = (double**) calloc (row1, sizeof (*c));

    for (int i = 0; i < row1; i++) {
        c[i] = (double*) calloc (col2, sizeof (*c[i]));

        for (int j = 0; j < col2; j++) {
            c[i][j] = 0;
            for (int k = 0; k < col1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }

    // Вывод матрицы произведения
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++)
            printf ("%lg ", c[i][j]);
        printf ("\n");
    }

    for (int i = 0; i < row1; i++) {
        free (a[i]);
        free (c[i]);
    }

    for (int i = 0; i < row2; i++) {
        free (b[i]);
    }

    free (a);
    free (b);
    free (c);

    return 0;
}
