#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char* word = NULL;

    int num_readed_symbs = 0;

    do
    {
        num_readed_symbs = scanf ("%ms[bom]", &word);

        if (num_readed_symbs > 0 && strcmp (word, "bomb") == 0)
        {
            printf ("YES\n");
            free (word);    
            return 0;
        }

        free (word); 
    }
    while (num_readed_symbs > 0);
    
    printf ("NO\n");
    return 0;
}