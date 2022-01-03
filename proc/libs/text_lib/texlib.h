#ifndef TEXLIB_H
#define TEXLIB_H

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#include <stdio.h>

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifndef PrintError
/// Макрос для OneginErrnoFunc, который автоматически подставляет
/// Файл и строку в сообщение об ошибке
#define PrintError(failed_function, error_text, log_file)                     \
  PrintErrorFunc (__FILE__, __LINE__, __PRETTY_FUNCTION__, failed_function,   \
                  error_text, log_file)
#endif

#ifndef CLOSE_FILE
/// Макрос для закрытия файла
#define CLOSE_FILE(file, func_name, ret)                                      \
  if (fclose (file) != 0)                                                     \
    {                                                                         \
      PrintError ((func_name), "Error while closing " #file, stderr);         \
      return ret;                                                             \
    }
#endif

#ifndef CHECK_FILE_OPENED
/// Макрос для проверки файла
#define CHECK_FILE_OPENED(file, func_name, ret)                               \
  if (!(file) || ferror (file))                                               \
    {                                                                         \
      PrintError ((func_name), "Error while opening " #file, stderr);         \
      return ret;                                                             \
    }
#endif

#ifndef CHECK_POINTER
/// Макрос для проверки указателя
#define CHECK_POINTER(ptr, func_name, ret)                                    \
  if (!(ptr))                                                                 \
    {                                                                         \
      PrintError ((func_name), "Error while allocating memory for " #ptr,     \
                  stderr);                                                    \
      return ret;                                                             \
    }
#endif

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
  char *ptr = nullptr;
  size_t len = 0;
  int position = 0;
} Line;

typedef struct
{
  size_t num_lines = 0;
  size_t non_empty_lines = 0;
  size_t text_size = 0;
  char *buf = nullptr;
  Line *lines;
} Text;

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TextCtor (Text *text, const char *filename);

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TextDtor (Text *text);

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

size_t CountSize (FILE *file);

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

ssize_t ReadFileToBuffer (char **file, const char *filename);

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CountSymbol (char *buffer, char symbol);

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FillLinesArray (char *buffer, Line *lines, int lines_num);

// flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SaveToFile (char* buffer, const char* filename);
int SaveLinesToFile (Text* text, FILE* file);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintErrorFunc (const char *file, const int line,
                     const char *current_function, const char *failed_function,
                     const char *error_text, FILE* log_file);
#endif
