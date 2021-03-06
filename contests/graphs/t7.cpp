#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);

    int **a = (int **) calloc(n, sizeof(*a));

    for (int i = 0; i < n; i++) {
        a[i] = (int *) calloc(n, sizeof(*a[i]));
    }

    int *d = (int *) calloc(n, sizeof(*d));     // минимальное расстояние
    int *v = (int *) calloc(n, sizeof(*v));     // посещенные вершины

    int temp, minindex, min;
    int begin_index = 0;

    // Инициализация матрицы связей
    int i_node = 0, j_node = 0, ij_weight = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &i_node, &j_node, &ij_weight);
        a[j_node][i_node] = ij_weight;
        a[i_node][j_node] = ij_weight;
    }

    // input begin index
    scanf("%d", &begin_index);

    //Инициализация вершин и расстояний
    for (int i = 0; i < n; i++) {
        d[i] = INT_MAX;
        v[i] = 1;
    }

    d[begin_index] = 0;

    // Шаг алгоритма
    do {
        minindex = INT_MAX;
        min = INT_MAX;

        for (int i = 0; i < n; i++) {   // Если вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min)) {  // Переприсваиваем значения
                min = d[i];
                minindex = i;
            }
        }

        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины

        if (minindex != INT_MAX) {
            for (int i = 0; i < n; i++) {
                if (a[minindex][i] > 0) {
                    temp = min + a[minindex][i];
                    if (temp < d[i]) {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < INT_MAX);

    // Вывод кратчайших расстояний до вершин
    for (int i = 0; i < n; i++)
        printf("%d ", d[i]);

    printf("\n");

    for (int i = 0; i < n; i++) {
        free(a[i]);
    }

    free(a);
    free(d);
    free(v);

    return 0;
}
