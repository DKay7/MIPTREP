#include "onegin.h"
#include <malloc.h>

int main (int argc, char* argv[])
{   
    const char* sort_filepath = "onegin.txt";
    const char* save_filepath = "onegin_sorted.txt";

    if (argc == 3)
    {
        sort_filepath = argv[1];
        save_filepath = argv[2];
    }

    int num_symbols = count_symbols (sort_filepath);
    char* file_buffer = (char*) calloc (num_symbols + 1, sizeof (char));

    if (!file_buffer)
    {
        print_error ("main", "Error while allocating memory for file buffer");
        return -1;
    }

    read_file_to_buffer (sort_filepath, file_buffer, num_symbols);

    int num_lines = count_lines (file_buffer);
    string** str_array = (string**) calloc (num_lines, sizeof (string*));

    if (!str_array)
    {
        print_error ("main", "Error while allocating memory for string array");
        return -1;
    }
    
    fill_array (file_buffer, str_array, num_lines, num_symbols);
    qsort (str_array, num_lines, sizeof (string*), lexicographic_comparator);
    save_to_file (str_array, save_filepath, num_lines);

    return 0;
}