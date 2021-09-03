/**
* @file
* @brief Данный файл содержит в себе прототипы функций для сортировки романа в стихах "Евгений Онегин".
*/

#include <stdio.h>

/// Макрос для print_error_func, который автоматически подставляет
/// Файл и строку в сообщение об ошибке
#define print_error(failed_function, error_text) print_error_func(__FILE__, __LINE__, __FUNCTION__, failed_function, error_text)

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
* @brief Функция qsort сортирует переданный массив.
*   
* @param [in] array Указатель на массив указателей для сортировки.
* @param [in] n_memb Количество элементов в массиве.
* @param [in] el_size Размер одного элемента в байтах.
* @param [in] start Левая граница сортируемого участка (индекс элемента массива).
* @param [in] end Правая граница сортируемого участка (индекс элемента массива).
* @param [in] comparator Указатель на функцию для сравнения элементов массива.
*/
void qsort (void* array, size_t n_memb,  size_t el_size,
            int (*comparator) (const void*, const void*));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция paritation разделяет массив вокруг опорного элемента.
* @details Данная функция используется внутри функции @link qsort @endlink, 
*          как часть алгоритма быстрой сортировки.
*
* @param [in, out] array Указатель на массив указателей для сортировки.
* @param [in] n_memb Количество элементов в массиве.
* @param [in] el_size Размер одного элемента в байтах.
* @param [in, out] left Указатель на левую границу сортируемого участка (индекс элемента массива).
* @param [in, out] right Указатель на правую границу сортируемого участка (индекс элемента массива).
* @param [in] pivot_index Индекс опорного элемента.
* @param [in] comparator Указатель на функцию для сравнения элементов массива.
*
* @return Возвращает индекс последнего элемента левой части массива.
*/
unsigned paritation (void* array, size_t n_memb, size_t el_size, unsigned pivot_index, 
                     int (*comparator) (const void*, const void*));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция swap меняет местами два элемента.
*
* @param [in,out] a Указатель на первый элемент.
* @param [in,out] b Указатель на второй элемент.
* @param [in] el_size Размер одного элемента в байтах.
*/
void swap (void* a, void* b, size_t el_size);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция choose_pivot выбирает в массиве опорный элемент.
*
* @param [in] n_memb Количество элементов в массиве.
* @return Индекс опорного элемента в массиве
*/
unsigned choose_pivot (size_t n_memb);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция lexicographic_comparator используется для лексиграфического
*        сравнения двух строк
*
* @param [in] string_1 Указатель на первую строку.
* @param [in] string_2 Указатель на втору строку.
* @return -1, если string_1 < string_2,
*          0, если string_1 == string_2,
*          1, если string_1 > string_2
*/
int lexicographic_comparator (const void* string_1, const void* string_2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция string_ctor инициализирует структуру данных @link string @endlink.                           
*
* @param [in] string Указатель на структуру @link string @endlink, которая будет заполнена данными
* @param [in] data Указатель на строку для парсинга.
* @param [in] len Длина строки.
*/
int string_ctor (string* string, char* data, size_t len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция count_symbols считает количество символов в файле.
*
* @param [in] buffer Указатель на буфер, из которого будут прочитаны данные.
* @return Количество строк в файле
*/
int count_symbols (const char* filename);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция read_file_to_buffer считывает файл в буфер.
*
* @param [in] filename Указатель на строку c путем до файла, из которого будут прочитаны данные.
* @param [out] buffer Указатель на буфер, из которого будут прочитаны данные.
* @param [in] num_symbols количество символов в файле.
*/
int read_file_to_buffer (const char* filename, char* buffer, int num_symbols);

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
* @brief Функция parse_file парсит файл со строками.
*
* @param [in] buffer Указатель на буфер, из которого будут прочитаны данные.
* @param [in] line_num Количество строк в файле.
* @param [in] num_symbols количество символов в файле.
* @param [out] array Указатель на массив структур @link string @endlink с 
*                    предобработанными строками из файла.
*/
int fill_array (char* buffer, string** array, unsigned line_num, unsigned num_symbols);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция save_file парсит файл со строками.
*
* @param [in] array Указатель на массив структур @link string @endlink.
* @param [in] filename Указатель на строку c путем до файла, в который будут записаны данные.
* @param [in] line_num Количество строк в файле.
*/
int save_to_file (string** array, const char* filename, unsigned line_num);

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
