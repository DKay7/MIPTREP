#include <stdio.h>

#define ll long long unsigned

int main ()
{   
    ll a = 0, b = 0;
    ll counter = 0;

    scanf ("%llu %llu", &a, &b);

    for (int i = 0; i < 8 * sizeof (a); i++)
    {
        ll a_bit = a & (0x1LLU << i);
        ll b_bit = b & (0x1LLU << i);

        if (a_bit != b_bit)
            ++ counter;
    }

    printf ("%llu", counter);

    return 0;
}