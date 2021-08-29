/**
* @file
* @brief Данный файл содержит в себе прототипы функций работы со строкаи, реализованных в проекте
*/

#include <stdio.h>

/// Макрос для print_error_func, который автоматически подставляет
/// Файл и строку в сообщение об ошибке
#define print_error(failed_function, error_text) print_error_func(__FILE__, __LINE__, __FUNCTION__, failed_function, error_text)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция выводит строку в stdout и добавляет символ новой строки 
*   
* @param [in] string Строка для вывода
*/
int puts (const char* string);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция выводит строку в stdout и добавляет символ новой строки 
*   
* @param [in] string Строка для вывода
* @param [in] symbol Символ для поиска
* @return Указатель на символ в данной строке
*/
char* strchr (char* string, int symbol);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция выводит длину строки без учета символа конца строки 
*   
* @param [in] string Строка для расчет длины
* @return Длина строки
*/
size_t strlen(char* string);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция выводит длину строки без учета символа конца строки 
*   
* @param [in] destptr Указатель на строку назначения, куда будет скопирована строка-источник.
* @param [in] srcptr Указатель на копируемую строку.
* @return Указатель на строку назначения.
*/
char* strcpy (char* destptr, const char* srcptr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция копирует первые num символов из строки srcptr в строку destptr 
*   
* @param [in] destptr Указатель на строку назначения, куда будут копироваться символы
* @param [in] srcptr Копируемая строка
* @param [in] num Максимальное количество копируемых символов строки
* @return Указатель на строку назначения.
*/
char* strncpy(char* destptr, const char* srcptr, size_t num);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция добавляет копию строки srcptr в конец строки destptr
*   
* @param [in] destptr Указатель на строку назначения, к которой добавятся символы строки srcptr.
* @param [in] srcptr Строка, которая добавляется в конец строки destptr.
* @return Указатель на строку назначения.
*/
char* strcat(char* destptr, const char* srcptr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция добавляет первые num символов строки srcptr к концу строки destptr
*   
* @param [in] destptr Указатель на строку назначения, к которой добавятся символы строки srcptr.
* @param [in] srcptr Строка, которая добавляется в конец строки destptr.
* @param [in] num Максимальное количество копируемых символов строки
* @return Указатель на строку назначения.
*/
char* strncat(char* destptr, const char* srcptr, size_t num);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция fgets считывает символы из потока и сохраняет их в виде строки 
*        в параметр string до тех пор пока не наступит конец строки или пока не 
*        будет достигнут конец файла.
*   
* @param [in] string Указатель на строку назначения, в которую сохраняются считанные символы.
* @param [in] num Максимальное количество символов для чтения, включая нулевой символ.
* @param [in] filestream Указатель на объект типа FILE, который идентифицирует поток, 
*                        из которого считываются символы.
* @return В случае успеха, функция возвращает указатель на строку назначения. 
*         Если конец файла был достигнут и ни один символ не был прочитан, возвращается нулевой указатель.
*         Если происходит ошибка, возвращается нулевой указатель.
*/
char* fgets(char* string, size_t num, FILE* filestream);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция strdup дублирует строку, на которую указывает аргумент str. 
*        Память под дубликат строки выделяется с помощью функции malloc, 
*        и по окончанию работы с дубликатом должна быть очищена с помощью функции free
*   
* @param [in] string Указатель на дублируемую строку
* @return В случае успеха, функция возвращает указатель на новую строку. 
*         NULL – в случае ошибки.
*/
char* strdup(const char* string);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
* @brief Функция считывает целую строку, сохраняя адрес буфера, содержащего текст, в *lineptr. 
*   
* @param [in] lineptr Указатель на буффер для считаваемой строки.
* @param [in] n Указатель на размер буффера.
* @param [in] streanm Указатель на файл для чтения
* @return При нормальном завершении работы функция возвращают количество считанных символов
*/
int getline(char** lineptr, size_t* n, FILE* streanm);

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
