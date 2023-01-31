#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char* word = NULL;

    int delta_coord = 0;
    int x_coord = 0;
    int y_coord = 0;

    while (scanf ("%ms", &word) && word[0] != 'T')
    {   
 
        delta_coord = 0;
        
        scanf ("%d", &delta_coord);

        switch (word[0])
        {
            case 'N':
                y_coord += delta_coord;
                break;
            
            case 'S':
                y_coord -= delta_coord;
                break;
            
            case 'E':
                x_coord += delta_coord;
                break;
            
            case 'W':
                x_coord -= delta_coord;
                break;
            
            default:
                break;
        }

        free (word);
    }
    
    free (word);

    printf ("%d %d\n", x_coord, y_coord);
    return 0;
}
