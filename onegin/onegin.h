/**
* @file
* @brief Данный файл содержит в себе прототипы функций для сортировки романа в стихах "Евгений Онегин".
*/

#include <stdio.h>

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
*         0, если string_1 == string_2,
*         1, если string_1 > string_2
*/
int lexicographic_comparator (const void* string_1, const void* string_2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция string_ctor инициализирует структуру данных @link string @endlink.                           
*
* @param [in] string Указатель на строку для парсинга.
* @param [in] len Длина строки.
* @return Указатель на структуру @link string @endlink
*/
string* string_ctor (char* string, size_t len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция parse_one_line парсит одну строку файла.
*
* @param [in] line Указатель на строку для парсинга.
* @return Указатель на структуру @link string @endlink
*/
string* parse_one_line (char* line);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция parse_file парсит файл со строками.
*
* @param [in] path Указатель на строку c путем до файла, из которого будут прочитаны данные.
* @return Указатель на массив структур @link string @endlink с 
*         предобработанными строками из файла.
*/
string** parse_file (char* path);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция save_file парсит файл со строками.
*
* @param [in] array Указатель на массив структур @link string @endlink.
* @param [in] path Указатель на строку c путем до файла, в который будут записаны данные.
*/
void save_to_file (string** array, char* path);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
