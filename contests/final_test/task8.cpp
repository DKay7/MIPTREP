#include <stdio.h>
#include <stdlib.h>

int Length(int num_n)
{
    int i, j = 1;
    for (i = 1; i < num_n; i++) {
        j = 2 * j + 1;
    }
    return j;
}

int CustomStrChr(int num_k, int num_n)
{
    if (num_n == 1) {
        return 1;
    }
    if (num_k == 1) {
        return num_n;
    }
    if (num_k > Length(num_n) / 2 + 1) {
        return CustomStrChr(num_k - Length(num_n) / 2 - 1, num_n - 1);
    }
    return CustomStrChr(num_k - 1, num_n - 1);
}

int main()
{

    int num_k, num_n;
    scanf("%d %d", &num_n, &num_k);
    printf("%c\n", CustomStrChr(num_k, num_n) + 'a' - 1);

    return 0;
}
