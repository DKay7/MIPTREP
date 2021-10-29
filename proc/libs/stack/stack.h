#ifndef STACK_H
#define STACK_H
/**
*   @file
*   @brief Файл содержит в себе прототипы функций для работы со стаком и саму структуру стака.
*/

#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifndef GREEN_COLOR
/// Макрос для окраски текста в зеленый цвет
#define GREEN_COLOR(text) ("\033[92m" text "\033[0m")
#endif



//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Макрос для окраски текста в красный цвет
#ifndef RED_COLOR
/// Макрос для окраски текста в красный цвет
#define RED_COLOR(text) "\033[91m" text "\033[0m"
#endif


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Макрос для функции \link StackDumpFunc, \endlink который автоматически подставляет строку, имя функции, имя файла и имя переменной.
#define StackDump(stack, file) StackDumpFunc (stack, file, __LINE__, __PRETTY_FUNCTION__, __FILE__, #stack)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Макрос для функции \link StackCtorFunc, \endlink который автоматически подставляет строку, имя функции, имя файла и имя переменной.
#define StackCtor(stack, size) StackCtorFunc (stack, size, #stack, __PRETTY_FUNCTION__, __LINE__, __FILE__)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#if !defined(STACK_DATA_POISON)
/// Макрос для константы яда для данных в стеке.
#define STACK_DATA_POISON 666
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifdef VALIDATE_ALL
/// Макрос для константы яда для данных в стеке. Если VALIDATE_ALL определено.
#define ValidateResult(stack, func_code) StackValidate(stack, func_code)
#else
/// Макрос для константы яда для данных в стеке. Если VALIDATE_ALL не определено.
#define ValidateResult(stack, func_code) STACK_OK
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define STACK_INCREASE_COEFFICIENT 2

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define STACK_DECREASE_COEFFICIENT 1.0 / 4.0

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Объявление типа стака. Необходимо, чтобы стак был независим от типа данных.
typedef double stack_type;

/// Объявление типа канарейки.
typedef unsigned long long hummingbird_type;
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const hummingbird_type HUMMINGBIRD = (hummingbird_type) 0xDEAD0DED;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/** @struct AdditionalInfo
*  @brief Дополнительные данные стека.
*/
typedef struct
{       
    unsigned int error_code;                         /**< Поле AdditionalInfo#error_code хранит код ошибки. */
    unsigned int error_func_code;                    /**< Поле AdditionalInfo#error_code хранит код функции, в которой произошла ошибка. */
    const char* filename;                   /**< Поле AdditionalInfo#filename хранит имя файла, в котором был проинициализирован стек. */
    int line;                               /**< Поле AdditionalInfo#line хранит номер строки, в которой был проинициализирован стек. */
    const char* stack_name;                 /**< Поле AdditionalInfo#stack_name хранит имя объекта стека. */
    const char* init_func;                  /**< Поле AdditionalInfo#stack_name хранит имя функции, в которой был проинициализирован стек. */
    void (*print_function)(stack_type*);    /**< Поле AdditionalInfo#print_function хранит указатель на функцию для распечатки значений. */
} AdditionalInfo;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/** @struct Stack
 *  @brief Структура стека.
 */
typedef struct Stack
{       
    hummingbird_type start_bird;            /**< Поле Stack#start_bird хранит канарейку начала структуры. */
    size_t size;                            /**< Поле Stack#size хранит размер занятого пространства. */
    size_t capacity;                        /**< Поле Stack#capacity хранит размер выделенной памяти. */
    stack_type* data;                       /**< Поле Stack#data хранит указатель на начало массива с данными. */
    unsigned long long hash;                /**< Поле Stack#hash хранит хэш стека.*/
    AdditionalInfo info;                    /**< Поле Stack#info хранит дополнительную информацию о структуре. */
    hummingbird_type end_bird;              /**< Поле Stack#end_bird хранит канарейку конца структуры. */
} Stack;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Перечисление кодов ошибок, которые функции работы со стаком возвращают.  
*/
enum RETURN_CODES
{
    #define DEF_ERR_CODE(enum_name, id, text)  \
        enum_name = id,                         \
    
    #include "defines/err_code_defines.h"

    #undef DEF_ERR_CODE
};

/**
*   Перечисление функций для отладки.  
*/
enum FUNC_CODES
{
    #define DEF_FUNC_CODE(enum_name, id, text)  \
        enum_name = id,                         \
    
    #include "defines/func_code_defines.h"

    #undef DEF_FUNC_CODE
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackCtorFunc конструирует объект стека.
*   
*   @note Вы также должны объявить тип данных стека \link stack_type \endlink и яд для данных:
*         #STACK_DATA_POISON
*
*   @param [in, out] stack  Указатель на структуру \link Stack \endlink.
*   @param [in] size        Начальный размер для аллоцирования буффера.
*   @param [in] stack_name  Имя переменной стека.
*   @param [in] line        Строка, в которой был вызван конструктор.
*   @param [in] func_name   Имя функции, в которой был вызван конструктор.
*   @param [in] file_name   Имя файла, в котором был вызван конструктор.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackCtorFunc (Stack* stack, size_t size, const char* stack_name, const char* func_name, int line, const char* file_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackDtor уничтожает объект стака.
*   
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackDtor (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackPoison заполняет ядом первые num элементов стека.
*   
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*   @param [in] start Индекс первого элемента для отравления.
*   @param [in] num Количество элементов для отравления.
*
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
void StackPoison (Stack* stack, size_t start, size_t num);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция SetStackPrinterFunc уничтожает объект стака.
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*   @param [in] printer_func Указатель на функцию для распечатки значений.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int SetStackPrinterFunc (Stack* stack, void (*printer_func)(stack_type*));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackPush пушит элемент в стак.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @param [in] element Элемент для пуша.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackPush (Stack* stack, stack_type element);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackPush попит элемент из стака.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @param [out] out_element Указатель на переменную, в котрую будет сохранено полученное значение.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackPop (Stack* stack, stack_type* out_element);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackIncrease увеличивает стак при необходимости.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackIncrease (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackDecrease уменьшает стак при необходимости.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackDecrease (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackDumpFunction выводит отладочную информацию о стаке.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @param [in] print_function Указатель на функцию для печати одного элемента стека. 
*   @param [in] line Номер строки, в которой вызвана данная функция.
*   @param [in] func_name Имя функции, в которой вызвана данная функция.
*   @param [in] file_name Имя файла, из которого вызвана данная функция.
*   @param [in] logfile Файл для записи ошибки.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackDumpFunc (Stack* stack, FILE* logfile, const int line, const char* func_name, const char* file_name, const char* stack_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackValidate проверяет, что со стеком все хорошо.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackValidate (Stack* stack, unsigned int func_code);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция HashSum считает универсальную хэш-сумму.
*   
*   @param [in] ptr Указатель на объект.
*   @param [in] size Размер объекта.
*   @return Хэш-сумму.
*/
unsigned long long HashSum(void* ptr, size_t size, unsigned long long hash = 0);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackHashSum считает хэш-сумму стека.
*   
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*   @return Хэш-сумму стека.
*/
unsigned long long StackHashSum(Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackPrintExitCode .
*   
*   @param [in] stack Указатель на объект стека.
*   @param [in] logfile Файл для записи ошибки.
*/
int StackPrintExitCode(Stack* stack, FILE* logfile);

/**
*   @brief Функция UnitTest проводит тестирование стака.
*/
int UnitTest ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#endif