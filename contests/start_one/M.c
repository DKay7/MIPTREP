#include <stdio.h>


int bonachi (int num);

//-----------------------------------------------------

int main ()
{   
    int num = 0, num_to_find = 0;

    scanf ("%d", &num);
    num_to_find = bonachi (num + 1);

    printf ("%d\n", num_to_find);

}

//-----------------------------------------------------

int bonachi (int num)
{
    if (num <= 3)
    {
        return 1;
    }

    return bonachi (num - 1) + bonachi (num - 2) + bonachi (num - 3);
}