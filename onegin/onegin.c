#include<stdio.h>


int puts (const char* string)
{   
    assert (string);

    int i = 0;

    for (i = 0; string[i] != EOF; i++)
    {
        int result_code = putchar (string[i]);
    }
}