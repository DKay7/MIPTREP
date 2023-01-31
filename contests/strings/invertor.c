#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char letter = 0;
    char not_alpha_letter = 0;

    char buffer[1000];
    char word[1000];
    int pointer = 0;

    int num_readed_symbs = 0;
    int buf_size = 0;

    while ((letter = getchar()))
    {
        if (isalpha (letter))
        {
            word[pointer] = letter;
            pointer += 1;
        }

        else
        {   
            not_alpha_letter = letter;
            int word_len = pointer;

            for (pointer; pointer > 0; pointer--)
            {
                buffer[buf_size + word_len - pointer] = word[pointer - 1];
                word[pointer] = 0;
            }

            buffer[buf_size + word_len] = not_alpha_letter;
            buf_size += word_len + 1;

            if (not_alpha_letter == '\n')
            {
                break;
            }

            pointer = 0;
        }
    }

    for (int i=0; i < buf_size; i++)
        printf ("%c", buffer[i]);

 

    return 0;
}