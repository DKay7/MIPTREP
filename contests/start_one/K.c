#include <stdio.h>

//-----------------------------------------------------

int main ()
{   
    int number = 0;
    int ones_counter = 0;

    scanf ("%d", &number);

    for (; number != 0; number>>=1)
    {   
        if (number & 1)
        {   
            ones_counter++;
        }

    }

    printf ("%d\n", ones_counter);

}

//-----------------------------------------------------