#include <malloc.h>
#include <stdio.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


double *gauss(double **a, double *y, int n)
{
    double *x, max;
    int k, index;
    const double eps = 0.00001; // точность
    x = (double *) calloc(n, sizeof(*x));

    k = 0;

    while (k < n) {
        // Поиск строки с максимальным a[i][k]
        max = fabs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(a[i][k]) > max) {
                max = fabs(a[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < eps) {
            // нет ненулевых диагональных элементов
            printf("NO\n");
            free (x);
            return NULL;
        }

        for (int j = 0; j < n; j++) {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        // Нормализация уравнений
        for (int i = k; i < n; i++) {
            double temp = a[i][k];
            if (fabs(temp) < eps)
                continue;       // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)
                continue;       // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }

    // обратная подстановка
    for (k = n - 1; k >= 0; k--) {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    double **a, *y, *x;
    int n = 3;

    a = (double **) calloc(n, sizeof(*a));
    y = (double *) calloc(n, sizeof(*y));


    for (int i = 0; i < n; i++) {
        a[i] = (double *) calloc(n, sizeof(*a[i]));

        for (int j = 0; j < n; j++) {
            scanf("%lg", &a[i][j]);
        }

        scanf("%lg", &y[i]);
    }

    x = gauss(a, y, n);

    if (!x) goto free_and_ret;
    
    for (int i = 0; i < n; i++)
        printf("%lg\n", x[i]);


    free_and_ret:
        for (int i = 0; i < n; i++) {
            free(a[i]);
        }

        free(a);
        free(y);
        free(x);

    return 0;
}
