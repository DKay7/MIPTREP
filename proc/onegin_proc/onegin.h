#ifndef ONEGIN_H
#define ONEGIN_H
/**
* @file
* @brief Данный файл содержит в себе прототипы функций для чтения/записи романа в стихах "Евгений Онегин" и трагедии "Гамлет".
*
* @note Если файл с произведением для сортировки содержит кириллические символы, то он обязательно должен быть в кодироке
*       iso88595. В противном случае, не гарантируется надлежащее сравнение символов файла.
*       Если же файл содержит только символы латиницы, он может быть в любой 8-битной кодировке.
*/

#include <stdio.h>

#ifndef OneginErrno
/// Макрос для OneginErrnoFunc, который автоматически подставляет
/// Файл и строку в сообщение об ошибке
#define OneginErrno(failed_function, error_text) OneginErrnoFunc(__FILE__, __LINE__, __PRETTY_FUNCTION__, failed_function, error_text)
#endif

#ifndef RED_COLOR
/// Макрос для окраски текста в красный цвет
#define RED_COLOR(text) "\033[91m" text "\033[0m"
#endif

#ifndef CLOSE_FILE
/// Макрос для закрытия файла
#define CLOSE_FILE(file, func_name, ret)  \
            if (fclose (file) != 0) \
            { \
                OneginErrno ((func_name), "Error while closing " #file); \
                return ret; \
            }
#endif

#ifndef CHECK_FILE_OPENED
/// Макрос для проверки файла
#define CHECK_FILE_OPENED(file, func_name, ret)  \
            if (!(file) || ferror (file)) \
            { \
                OneginErrno ((func_name), "Error while opening " #file); \
                return ret; \
            }
#endif

#ifndef CHECK_POINTER
/// Макрос для проверки указателя
#define CHECK_POINTER(ptr, func_name, ret)  \
            if (!(ptr)) \
            { \
                OneginErrno ((func_name), "Error while allocating memory for " #ptr); \
                return ret; \
            }
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/** @struct String
 *  @brief Структура для представления строки в программе.
 */
typedef struct String 
{
    size_t len;     /**< Поле String#len хранит длину строки. */
    char* start;    /**< Поле String#start хранит указатель на начало строки. */
} String;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция StringCtor инициализирует структуру данных @link String @endlink.                           
*
* @param [in, out] String Указатель на структуру @link String @endlink, которая будет заполнена данными.
* @param [in] data Указатель на начало строки для сохранения в структуру.
* @param [in] len Длина строки.
*/
int StringCtor (String* String, char* data, size_t len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция CountSymbols считает количество символов в файле.
*
* @param [in] file Файловый дескриптов, через который будут прочитаны данные.
* @return Количество символов в файле
*/
int CountSymbols (FILE* file);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция ReadFileToBuffer считывает файл в буфер.
*
* @param [in] file Файловый дескриптов, через который будут прочитаны данные.
* @param [out] buffer Указатель на буфер, в который будут сохранены данные.
* @param [in] num_symbols количество символов в файле.
*
* @note Если файл содержит кириллические символы, то он обязательно должен быть в кодироке
*       iso88595. В противном случае, не гарантируется надлежащее сравнение символов файла.
*       Если же файл содержит только символы латиницы, он может быть в любой 8-битной кодировке.
*/
char* ReadFileToBuffer (FILE* file, int num_symbols);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция CountLines считает количество строк в файле.
*
* @param [in] buffer Указатель на буффер, из которого будут прочитаны данные.
* @return Количество строк в файле
*/
int CountLines (char* buffer);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция OneginFillPArray заполняет массив указателей на структуры строк данными из буфера.
*
* @param [in] buffer Указатель на буфер, из которого будут прочитаны данные.
* @param [out] ptr_array Указатель на массив указателей на структуры @link String @endlink,
*                        в него будут сохранены указатели на структуры.
* @param [out] str_array Указатель на массив структур @link String @endlink,
*                        в него будут сохранены сами структуры.
* @param [in] line_num Количество строк в файле.
* @param [in] num_symbols количество символов в файле.
*/
int OneginFillPArray (char* buffer, String** ptr_array, String* str_array, 
                unsigned line_num, unsigned num_symbols);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция save_file сохраняет массив указателей на строки в файл.
*
* @param [in] array Указатель на массив указателей на структуры @link String @endlink.
* @param [in] file Файловый дескриптоп, через который будут записаны данные.
* @param [in] line_num Количество строк в файле.
*/
int OneginSavePArrToFile (String** array, FILE* file, unsigned line_num);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция OneginSaveOrigToFile сохраняет массив строк (исходный, неизмененный массив) в файл.
*
* @param [in] array Указатель на массив структур @link String @endlink.
* @param [in] file Файловый дескриптоп, через который будут записаны данные.
* @param [in] line_num Количество строк в файле.
*/
int OneginSaveOrigToFile (String* array, FILE* file, unsigned line_num);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция выводит информацию об ошибке в stderr
* 
* @param[in] file Файл, в котором произошла ошибка
* @param[in] line Строка в которой произошла ошибка
* @param[in] current_function Имя функции, из которой была вызвана \link OneginErrnoFunc \endlink
* @param[in] failed_function Имя функции, в которой возникла ошибка
* @param[in] error_text Текст ошибки
* @return Указатель на символ в данной строке
*/
void OneginErrnoFunc (const char* file, const int line, const char* current_function, 
                       const char* failed_function, const char* error_text);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#endif