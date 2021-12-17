#include <stdio.h>
#include <string.h>

char* strbin(char* dst, unsigned int x) 
{   
    char* dst_old = dst;
    char* for_return = dst;

    if (x == 0)
    {
        sprintf (dst, "0");
    }

    while(x > 0)
    {   
        sprintf (dst, "%d", x % 2);
        dst += 1;

        x /= 2;
    }
    

    char temp;
    char* end = dst_old + strlen(dst_old);

    while( dst_old < --end ) 
    {
        temp = *dst_old;
        *dst_old = *end;
        *end = temp;
        ++dst_old;
    }

    return for_return;
}

int main ()
{   
    char dst[100];
    printf("%s\n", strbin(dst, 126));   // напечатает 101
    return 0;
}