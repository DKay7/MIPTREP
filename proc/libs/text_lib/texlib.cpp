#include "texlib.h"
#include <string.h>
#include <assert.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TextCtor (Text* text, const char* filename)
{
    assert (text);
    assert (filename);

    text->text_size = ReadFileToBuffer (&(text->buf), filename);
    text->num_lines = CountSymbol(text->buf, '\n');
    text->lines = (Line*) calloc (text->num_lines, sizeof (*text->lines));
    text->non_empty_lines = FillLinesArray (text->buf, text->lines, text->num_lines);

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

int CountSize (FILE* file)
{   
    assert (file);
    
    fseek (file, 0, SEEK_END);
    int num_sumbols = ftell (file);
    fseek (file, 0, SEEK_SET);

    return num_sumbols;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

ssize_t ReadFileToBuffer (char** buf, const char* filename)
{   
    assert (buf);
    assert (filename);

    FILE* file = fopen (filename, "r");
    CHECK_FILE_OPENED (file, "ReadFileToBuffer", 0);
    
    size_t num_symbols = CountSize (file);
    *buf = (char*) calloc (num_symbols + 3, sizeof (**buf));
    CHECK_POINTER (*buf, "ReadFileToBuffer", 0);

    **buf = '\0';
    fread (*buf + 1, sizeof (**buf), num_symbols, file);

    if ( *(*buf + num_symbols) != '\n')
    {
        *(*buf + num_symbols + 1) = '\n';
        *(*buf + num_symbols + 2) = '\0';
    }

    CLOSE_FILE (file, "ReadFileToBuffer", 0);

    return num_symbols;
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

    char *right_ptr = NULL;
    char *left_ptr = buffer;
    int position = 0;

    for (int i_line = 0; i_line < lines_num; i_line++)
    {   
        int empty_counter = 0;

        do
        {   
            ++empty_counter;
            ++position;
            right_ptr = left_ptr + 1;

            left_ptr = strchr (right_ptr, '\n');

        } while (left_ptr && (*left_ptr == '\r' || left_ptr - right_ptr  < 1));

        --empty_counter;
        lines_num -= empty_counter;

        if (left_ptr)
        {   
            lines[i_line].ptr = right_ptr;
            lines[i_line].len = left_ptr - right_ptr + 1;
            lines[i_line].position = position;

            *left_ptr = '\0';
        }

        else
        {   
            left_ptr = strchr (right_ptr + 1, '\0');
            if (left_ptr && (left_ptr - right_ptr - 1) > 0)
            {   
                lines[i_line].ptr = right_ptr;
                lines[i_line].len = left_ptr - right_ptr - 1;
                lines[i_line].position = position;
                *left_ptr = '\0';
            }
        }
    }

    assert (lines_num > 0);
    return lines_num;
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
