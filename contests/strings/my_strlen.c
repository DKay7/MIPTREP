#include <stdio.h>

size_t my_strlen (const char* string)
{
    size_t i = 0;

    for (i; string[i] != '\0'; i++);

    return i;
}
