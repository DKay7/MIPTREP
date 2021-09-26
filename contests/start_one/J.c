#include <stdio.h>

//-----------------------------------------------------

int main ()
{   
    int number_to_find = 0, num_lines = 0, current_number = 0;
    int counter = 0;

    scanf ("%d %d", &number_to_find, &num_lines);

    for (int i=0; i < num_lines; i++)
    {
        scanf ("%d", &current_number);

        if (current_number == number_to_find)
        {
            counter += 1;
        }
    }

    printf ("%d\n", counter);

}

//-----------------------------------------------------