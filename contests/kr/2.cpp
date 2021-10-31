#include <stdio.h>

#define lld double
#define ll  long long unsigned 


int main ()
{   
    lld total_square = 0;
    lld i_square = 1;
    ll  n = 0;

    scanf ("%llu ", &n);

    for (ll i = 0; i < n; i++)
    {   
        ll num_papers = 0;

        scanf ("%llu", &num_papers);

        total_square += i_square * num_papers; 
        i_square /= 2;
    }


    printf ("%d\n", (int) total_square);

    return 0;
}