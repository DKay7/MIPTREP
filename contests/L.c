#include <stdio.h>

//-----------------------------------------------------

int main ()
{   
    int num_numbers = 0, current_num = 0;
    int sum = 0, flag = 1;

    scanf ("%d", &num_numbers);

    for (int i =0; i < num_numbers; i++)
    {  
        scanf ("%d", &current_num);
        sum += flag * current_num;
        flag *= -1;
    }

    printf ("%d\n", sum);

}

//-----------------------------------------------------