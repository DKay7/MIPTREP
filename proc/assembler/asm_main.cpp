#include "asm.h"
#include "malloc.h"
#include "string.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char** argv)
{   
    if (argc < 2)
    {   
        fprintf (stderr, "Not enough args\n");
        return -1;
    }

    if (argc > 4)
    {
        fprintf (stderr, "Too much args\n");
        return -1;
    }

    char* input_filename = argv[1];
    int   input_filename_len = strlen (input_filename);
    char*  output_filename = NULL;  
    char*  listing_filename = NULL;

    int was_names_created = 0;

    if (argc < 4)
    {   
        output_filename = (char*) calloc (input_filename_len + 1, sizeof(char));
        listing_filename = (char*) calloc (input_filename_len + 1, sizeof(char));
        
        if (!output_filename || !listing_filename)
        {
            fprintf (stderr, "Error allocating memory for output filenames\n");
            return -1;
        }

        int ret_code = GetOutputFileNames (input_filename, output_filename, listing_filename, input_filename_len);

        if (!ret_code)
        {
            fprintf (stderr, "Can't create output filename. Maybe input filename is wrong.\n");
            return -1;
        }

        was_names_created = 1;
    }

    else if (argc == 4)
    {   
        output_filename = argv[2];
        listing_filename = argv[3];
    }

    Text code = {};
    TextCtor (&code, argv[1]);

    AsmCompiler acc = {};
    long unsigned int cmd_arr_size = FindCmdArraySize (&code);
    AsmCompilerCtor (&acc, cmd_arr_size);

    CompileCode (&acc, &code, output_filename, listing_filename);

    AsmDumpFunction (&acc, stderr);
    TextDtor (&code);
    AsmCompilerDtor (&acc);

    if (was_names_created)
    {
        free (output_filename);
        free (listing_filename);
    }

    return 0;
}
