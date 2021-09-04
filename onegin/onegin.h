/**
* @file
* @brief Данный файл содержит в себе прототипы функций для чтения/записи романа в стихах "Евгений Онегин".
*/

#include <stdio.h>

/// Макрос для print_error_func, который автоматически подставляет
/// Файл и строку в сообщение об ошибке
#define print_error(failed_function, error_text) print_error_func(__FILE__, __LINE__, __FUNCTION__, failed_function, error_text)

/// Макрос для окраски текста в красный цвет
#define RED_COLOR(text) "\033[91m" text "\033[0m"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/** @struct string
 *  @brief Структура для представления строки в программе.
 */
typedef struct string 
{
    size_t len;     /**< Поле string#len хранит длину строки. */
    char* start;    /**< Поле string#start хранит указатель на начало строки. */
} string;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция string_ctor инициализирует структуру данных @link string @endlink.                           
*
* @param [in, out] string Указатель на структуру @link string @endlink, которая будет заполнена данными.
* @param [in] data Указатель на начало строки для сохранения в структуру.
* @param [in] len Длина строки.
*/
int string_ctor (string* string, char* data, size_t len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция count_symbols считает количество символов в файле.
*
* @param [in] file Файловый дескриптов, через который будут прочитаны данные.
* @return Количество символов в файле
*/
int count_symbols (FILE* file);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция read_file_to_buffer считывает файл в буфер.
*
* @param [in] file Файловый дескриптов, через который будут прочитаны данные.
* @param [out] buffer Указатель на буфер, в который будут сохранены данные.
* @param [in] num_symbols количество символов в файле.
*/
int read_file_to_buffer (FILE* file, char* buffer, int num_symbols);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция count_lines считает количество строк в файле.
*
* @param [in] buffer Указатель на буффер, из которого будут прочитаны данные.
* @return Количество строк в файле
*/
int count_lines (char* buffer);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция fill_array заполняет массив указателей на структуры строк данными из буфера.
*
* @param [in] buffer Указатель на буфер, из которого будут прочитаны данные.
* @param [out] ptr_array Указатель на массив указателей на структуры @link string @endlink,
*                        в него будут сохранены указатели на структуры.
* @param [out] str_array Указатель на массив структур @link string @endlink,
*                        в него будут сохранены сами структуры.
* @param [in] line_num Количество строк в файле.
* @param [in] num_symbols количество символов в файле.
*/
int fill_array (char* buffer, string** ptr_array, string* str_array, 
                unsigned line_num, unsigned num_symbols);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция save_file сохраняет массив указателей на строки в файл.
*
* @param [in] array Указатель на массив указателей на структуры @link string @endlink.
* @param [in] file Файловый дескриптоп, через который будут записаны данные.
* @param [in] line_num Количество строк в файле.
*/
int save_to_file (string** array, FILE* file, unsigned line_num);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция save_original_to_file сохраняет массив строк (исходный, неизмененный массив) в файл.
*
* @param [in] array Указатель на массив структур @link string @endlink.
* @param [in] file Файловый дескриптоп, через который будут записаны данные.
* @param [in] line_num Количество строк в файле.
*/
int save_original_to_file (string* array, FILE* file, unsigned line_num);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция выводит информацию об ошибке в stderr
* 
* @param[in] file Файл, в котором произошла ошибка
* @param[in] line Строка в которой произошла ошибка
* @param[in] current_function Имя функции, из которой была вызвана \link print_error_func \endlink
* @param[in] failed_function Имя функции, в которой возникла ошибка
* @param[in] error_text Текст ошибки
* @return Указатель на символ в данной строке
*/
void print_error_func (const char* file, const int line, const char* current_function, 
                       const char* failed_function, const char* error_text);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
