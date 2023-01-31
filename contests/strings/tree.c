#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char symbol = 0;
    char digit_buffer[1000];

    double multiplicator_accum = 1;
    double result = 0;
    
    while ((symbol = getchar()) != '\n')
    {
        if (isdigit (symbol) || symbol == '-')
        {   
            int i = 0;
            while (isdigit (symbol) || symbol == '-')
            {   
                digit_buffer[i] = symbol;
                symbol = getchar();
                i++;
            }

            if (!isdigit (symbol) && symbol != '-')
            {
                ungetc (symbol, stdin);
            }

            digit_buffer[i] = 0;
            result += multiplicator_accum * atoi (digit_buffer);
        }

        else
        {   
            switch (symbol)
            {
            case '(':
                multiplicator_accum *= 0.5;
                break;
            
            case ')':
                multiplicator_accum /= 0.5;
                break;

            default:
                break;
            }
        }
    }

    printf ("%.2lf\n", result);
    
    return 0;
}