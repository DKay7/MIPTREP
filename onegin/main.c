#include "onegin.h"
#include "qsort.h"
#include <malloc.h>
#include <locale.h>

int main (int argc, char* argv[])
{   
    // setting 8-bit iso locale to working correctly with cyrillic characters
    setlocale (LC_CTYPE, "ru_RU.iso88595");

    const char* sort_filepath = "hamlet.txt";
    const char* save_filepath = "hamlet_sorted.txt";

    if (argc == 3)
    {
        sort_filepath = argv[1];
        save_filepath = argv[2];
    }

    FILE* sort_file = fopen (sort_filepath, "r");
    FILE* save_file = fopen (save_filepath, "w");

    CHECK_FILE_OPENED (sort_file, "main", -1);
    CHECK_FILE_OPENED (save_file, "main", -1);

    int num_symbols = count_symbols (sort_file);
    char* file_buffer = read_file_to_buffer (sort_file, num_symbols);
    CLOSE_FILE (sort_file, "main", -1);

    int num_lines = count_lines (file_buffer);
    string** ptr_array = (string**) calloc (num_lines, sizeof (string*));
    string* str_array = (string*) calloc (num_lines, sizeof (string));

    CHECK_POINTER (ptr_array, "main", -1);
    CHECK_POINTER (str_array, "main", -1);
    
    fill_array (file_buffer, ptr_array, str_array, num_lines, num_symbols);

    qsort (ptr_array, num_lines, sizeof (string*), lexicographic_comparator);
    save_to_file (ptr_array, save_file, num_lines);

    qsort (ptr_array, num_lines, sizeof (string*), reversed_lexicographic_comparator);
    save_to_file (ptr_array, save_file, num_lines);

    save_original_to_file (str_array, save_file, num_lines);

    CLOSE_FILE (save_file, "main", -1);
    return 0;
}