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
* @param [in] array Указатель на сортируемый массив.
* @param [in] start Левая граница сортируемого участка.
* @param [in] end Правая граница сортируемого участка.
* @param [in] comp Функция для сравнения элементов массива.
*/
void qsort (void* array, int start, int end, int (*comp) (void*, void*));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция paritation разделяет массив вокруг опорного элемента.
* @details Данная функция используется внутри функции @link qsort @endlink, 
*          как часть алгоритма быстрой сортировки.
*
* @param [in] array Указатель на сортируемый массив.
* @param [in] start Указатель на левую границу сортируемого участка.
* @param [in] end Указатель на правую границу сортируемого участка.
* @param [in] pivot Опорный элемент.
*/
void paritation (void* array, int* start, int* end, int pivot);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция swap меняет местами два элемента.
*
* @param [in,out] a Указатель на первый элемент.
* @param [in,out] b Указатель на второй элемент.
*/
void swap (void* a, void* b);

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
int lexicographic_comparator (void* string_1, void* string_2);

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
