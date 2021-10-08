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

    size_t num_symbols = CountSymbols (sort_file);
    char* file_buffer = ReadFileToBuffer (sort_file, num_symbols);
    CLOSE_FILE (sort_file, "main", -1);

    size_t num_lines = CountLines (file_buffer);
    String** ptr_array = (String**) calloc (num_lines, sizeof (String*));
    String* str_array = (String*) calloc (num_lines, sizeof (String));

    CHECK_POINTER (ptr_array, "main", -1);
    CHECK_POINTER (str_array, "main", -1);
    
    OneginFillPArray (file_buffer, ptr_array, str_array, num_lines, num_symbols);

    qsort (ptr_array, num_lines, sizeof (String*), lexicographic_comparator);
    OneginSavePArrToFile (ptr_array, save_file, num_lines);

    qsort (ptr_array, num_lines, sizeof (String*), reversed_lexicographic_comparator);
    OneginSavePArrToFile (ptr_array, save_file, num_lines);

    OneginSaveOrigToFile (str_array, save_file, num_lines);

    CLOSE_FILE (save_file, "main", -1);

    free (file_buffer);
    free (str_array);
    free (ptr_array);

    return 0;
}
