#include <stdio.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define N 100
struct _Decimal {
    char a[N];                  // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;             // наибольшая степень десяти
};

typedef struct _Decimal Decimal;

Decimal zero = { { 0 }, 0 };    // представление 0 в виде структуры

void print(const Decimal * data);
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void mult10n(Decimal * res, const Decimal * a, unsigned int k)
{
    if (a->n == 0 && a->a[0] == 0) {
        res->n = 0;
        res->a[0] = 0;
        return;
    }

    for (unsigned int i = 0; i < k; ++i) {
        res->a[i] = 0;
    }

    res->n = k + a->n;

    for (unsigned int i = 0; i <= a->n; ++i) {
        res->a[k + i] = a->a[i];
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Decimal *div10n(const Decimal * a, unsigned int n)
{   
    Decima; new
    if (a->n == 0 && a->a[0] == 0) {
        return a;
    }

    for (int i = n; i >= 0; --i) {
        a->a[i] = 0;
    }

    unsigned int new_len = (a->n - n);
    a->n = (new_len > 0) ? new_len : 0;

    return a;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void print(const Decimal * data)
{

    for (int i = data->n; i >= 0; --i)
        printf("%d", data->a[i]);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    Decimal a = { { 9 }, 0 };   // set number 147

    Decimal *new_a = div10n(&a, 2);     // res = a*100 = 147*100 = 14700

    print(&new_a);              // print 147
    printf("\n");

    return 0;
}
