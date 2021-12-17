#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <malloc.h>

#define INF 257 // INT_MAX 

int main()
{
    int n = 0, m = 0;
    int weights_sum = 0;
    scanf("%d %d", &n, &m);

    int **G = (int **) calloc(n, sizeof(*G));

    for (int i = 0; i < n; i++) {
        G[i] = (int *) calloc(n, sizeof(*G[i]));
        memset (G[i], -1, sizeof (int) * n);
    }

    int i_node = 0, j_node = 0, ij_weight = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &i_node, &j_node, &ij_weight);
        G[j_node][i_node] = ij_weight;
        G[i_node][j_node] = ij_weight;
    }


    int no_edge;
    bool *selected = (bool *) calloc(n, sizeof(*selected));

    no_edge = 0;

    selected[0] = true;

    int x;
    int y;

    while (no_edge < n - 1) {
        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < n; i++) {
            if (selected[i]) {
                for (int j = 0; j < n; j++) {
                    if (!selected[j] && G[i][j] >= 0) {
                        if (min > G[i][j]) {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }

                    }
                }
            }
        }
        weights_sum += G[x][y];
        selected[y] = true;
        no_edge++;
    }

    printf("%d\n", weights_sum);

    for (int i = 0; i < n; i++) {
        free(G[i]);
    }

    free(G);
    free(selected);

    return 0;
}
