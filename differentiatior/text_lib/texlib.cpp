#include "texlib.h"
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TextCtor (Text* text, const char* filename)
{
    assert (text);
    assert (filename);

    text->text_size = (size_t) ReadFileToBuffer (&(text->buf), filename);

    int num_lines = CountSymbol(text->buf, '\n');
    text->num_lines =  (size_t) num_lines;

    text->lines = (Line*) calloc (text->num_lines, sizeof (*(text->lines)));

    text->non_empty_lines = (size_t) FillLinesArray (text->buf, text->lines, num_lines);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TextDtor (Text* text)
{
    assert (text);
    assert (text->buf);
    assert (text->lines);

    free (text->buf);
    free (text->lines);
    
    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

size_t CountSize (FILE *file)
{   
    assert (file);

    struct stat buff;
    fstat (fileno (file), &buff);
    return (size_t) buff.st_size;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

ssize_t ReadFileToBuffer (char** buf, const char* filename)
{   
    assert (buf);
    assert (filename);

    FILE* file = fopen (filename, "r");
    CHECK_FILE_OPENED (file, "ReadFileToBuffer", 0);
    
    size_t num_symbols = CountSize (file);
    *buf = (char*) calloc (num_symbols + 2, sizeof (char));

    CHECK_POINTER (*buf, "ReadFileToBuffer", 0);

    fread (*buf, sizeof (**buf), num_symbols, file);

    *(*buf + num_symbols) = '\n';
    *(*buf + num_symbols + 1) = '\0';

    CLOSE_FILE (file, "ReadFileToBuffer", 0);

    return (ssize_t) num_symbols;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CountSymbol (char* buffer, char symbol)
{   
    assert (buffer);

    int n_symbols = 0;

    if (*buffer == symbol)
    {
        ++n_symbols;
    }

    while ((buffer = strchr (buffer + 1, symbol)))
    {
        ++n_symbols;
    }

    return n_symbols;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FillLinesArray (char* buffer, Line* lines, int lines_num)
{   
    assert (buffer);
    assert (lines);
    assert (lines_num > 0);

    char* line_start_ptr = NULL;
    char* line_end_ptr = buffer - 1;

    int empty_counter = 0;
    int position = 0;

    for (int i_line = 0; i_line < lines_num; i_line++)
    {   
        empty_counter = 0;

        do
        {   
            line_start_ptr = line_end_ptr + 1;
            line_end_ptr = strchr(line_start_ptr, '\n');

            position ++;
            empty_counter++;

        } while  (line_end_ptr && (line_end_ptr - line_start_ptr) < 1);

        lines_num -= --empty_counter;

        
        if (line_end_ptr)
        {   
            lines[i_line].ptr = line_start_ptr;
            lines[i_line].position = position;
            lines[i_line].len = (size_t) (line_end_ptr - line_start_ptr + 1);
            *line_end_ptr = '\0';
        }

        else
        {
            line_end_ptr = strchr (line_start_ptr, '\0');
            if (line_end_ptr && line_end_ptr - line_end_ptr)
            {
                lines[i_line].ptr = line_start_ptr;
                lines[i_line].position = position;
                lines[i_line].len = (size_t) (line_end_ptr - line_start_ptr - 1);

                *line_end_ptr = '\0';
            }
        }
    }
    assert (lines_num > 0);
    return lines_num;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SaveLinesToFile (Text* text, FILE* file)
{   
    int num_writed = 0;

    for (size_t i = 0; i < text->non_empty_lines; i ++)
            num_writed += fprintf (file, "%s\n", text->lines[i].ptr);

    return num_writed;
}

int SaveToFile (char* buffer, const char* filename)
{   
    FILE* file = fopen (filename, "w");
    CHECK_FILE_OPENED (file, "SaveToFile", -1);

    int num_writed = fprintf (file, "%s", buffer);

    CLOSE_FILE (file, "SaveToFile", -1);

    return num_writed;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintErrorFunc (const char* file, const int line, const char* current_function, const char* failed_function, const char* error_text, FILE* log_file)
{   
    assert (file);
    assert (line);
    assert (current_function);
    assert (failed_function);
    assert (error_text);
  
    if (!log_file || ferror(log_file))
    {
        log_file = stderr;
    }

    fprintf (log_file, "File: %s\n"
                       "Line: %d\n"
                       "Current function: %s()\n"
                       "Failed function: %s()\n"
                       "Error message: %s\n",
                    file, line, current_function, failed_function, error_text);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
