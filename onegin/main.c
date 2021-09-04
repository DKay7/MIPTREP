#include "onegin.h"
#include "qsort.h"
#include <malloc.h>

int main (int argc, char* argv[])
{   
    const char* sort_filepath = "hamlet.txt";
    const char* save_filepath = "hamlet_sorted.txt";

    if (argc == 3)
    {
        sort_filepath = argv[1];
        save_filepath = argv[2];
    }

    FILE* sort_file = fopen (sort_filepath, "r");
    FILE* save_file = fopen (save_filepath, "w");

    if (!sort_file || ferror (sort_file))
    {
        print_error ("main", "Error while opening file to sort");
        return -1;
    }

    if (!save_file || ferror (save_file))
    {
        print_error ("main", "Error while opening file to save");
        return -1;
    }

    int num_symbols = count_symbols (sort_file);
    char* file_buffer = (char*) calloc (num_symbols + 1, sizeof (char));

    if (!file_buffer)
    {
        print_error ("main", "Error while allocating memory for file buffer");
        return -1;
    }

    read_file_to_buffer (sort_file, file_buffer, num_symbols);

    if (fclose (sort_file) != 0)
    {
        print_error ("main", "Error while closing file to sort");
        return -1;
    }

    int num_lines = count_lines (file_buffer);
    string** ptr_array = (string**) calloc (num_lines, sizeof (string*));
    string* str_array = (string*) calloc (num_lines, sizeof (string));

    if (!ptr_array)
    {
        print_error ("main", "Error while allocating memory for string's-pointers array");
        return -1;
    }

    if (!str_array)
    {
        print_error ("main", "Error while allocating memory for strings array");
        return -1;
    }
    
    fill_array (file_buffer, ptr_array, str_array, num_lines, num_symbols);

    qsort (ptr_array, num_lines, sizeof (string*), lexicographic_comparator);
    save_to_file (ptr_array, save_file, num_lines);

    qsort (ptr_array, num_lines, sizeof (string*), reversed_lexicographic_comparator);
    save_to_file (ptr_array, save_file, num_lines);

    save_original_to_file (str_array, save_file, num_lines);

    if (fclose (save_file) != 0)
    {
        print_error ("main", "Error while closing file to save");
        return -1;
    }

    return 0;
}