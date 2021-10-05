/**
*   @file
*   @brief Файл содержит в себе прототипы функций для работы со стаком и саму структуру стака.
*/

#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define GREEN_COLOR(text) ("\033[92m" text "\033[0m")
#define RED_COLOR(text) ("\033[91m" text "\033[0m")

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define StackDump(stack) StackDumpFunc (stack, __LINE__, __PRETTY_FUNCTION__, __FILE__, #stack)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define StackCtor(stack, size) StackCtorFunc (stack, size, #stack, __PRETTY_FUNCTION__, __LINE__, __FILE__)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifndef STACK_DATA_POISON
#define STACK_DATA_POISON 0xDEAD
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifdef VALIDATE_ALL
#define ValidateResult(stack, func_code) StackValidate(stack, func_code)
#else
#define ValidateResult(stack, func_code) STACK_OK
#endif

/// Объявление типа стака. Необходимо, чтобы стак был независим от типа данных.
typedef int stack_type;
typedef unsigned long long hummingbird_type;
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const hummingbird_type HUMMINGBIRD = (hummingbird_type) 0xDEAD0DED;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/** @struct AdditionalInfo
 *  @brief Дополнительные данные стека.
 */
typedef struct AdditionalInfo
{       
    int error_code;                         /**< Поле AdditionalInfo#error_code хранит код ошибки. */
    int error_func_code;                    /**< Поле AdditionalInfo#error_code хранит код функции, в которой произошла ошибка. */
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
    STACK_OK =                          0x00000000,     // Все ОК.
    STACK_MEM_ALLOCK_ERR =              0x00000001,     // Ошибка аллоцирования / реаллоцирования памяти.
    STACK_INCREASE_ERR =                0x00000002,     // Ошибка в функции увеличения размера стека.
    STACK_DECREASE_ERR =                0x00000004,     // Ошибка в функции уменьшения размера стека.
    STACK_CTOR_DBL_CALL =               0x00000008,     // Двойной вызов конструктора.
    STACK_DTOR_DBL_CALL =               0x00000010,     // Двойной вызов деструктора.
    STACK_INCORRECT_DATA_PTR =          0x00000020,     //  Неверный указатель на данные.
    STACK_WRONG_START_HUMMINGBIRD =     0x00000040,     //  Неверная начальная канарейка.
    STACK_WRONG_END_HUMMINGBIRD =       0x00000080,     //  Неверная конечная канарейка.
    STACK_INCORRECT_SIZE =              0x00000100,     //  Неверный размер стека.
    STACK_INCORRECT_CAPACITY =          0x00000200,     //  Неверный размер стека.
    STACK_WRONG_HASH_SUM =              0x00000400      //  Неверный размер стека.
};

/**
*   Перечисление функций для отладки.  
*/
enum FUNC_CODES
{
    STACK_CTOR_CODE  =           0x00000001,
    STACK_DTOR_CODE =            0x00000002,
    STACK_PUSH_CODE =            0x00000004,
    STACK_POP_CODE =             0x00000008,
    STACK_INCREASE_CODE =        0x00000010,
    STACK_DECREASE_CODE =        0x00000020,
    STACK_DUMP_CODE =            0x00000040,
    STACK_UNIT_TEST_CODE =       0x00000080,
    STACK_SET_PRINTER_CODE =     0x00000100,
    STACK_PRINT_EXIT_CODE_CODE = 0x00000200,
    STACK_VALIDATE_CODE =        0x00000400
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackCtorFunc конструирует объект стека.
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
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackDumpFunc (Stack* stack, const int line, const char* func_name, const char* file_name, const char* stack_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackValidate проверяет, что со стеком все хорошо.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackValidate (Stack* stack, const int func_code);

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
*   @brief Функция CheckStackHash проверяет хэш-сумму стека на корректность.
*   
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*   @return 1, если хэш-сумма текущего состояния стека равна сохраненной хэш-сумме, иначе 0
*/
int CheckStackHash (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackPrintExitCode .
*   
*   @param [in] stack Указатель на объект стека.
*/
int StackPrintExitCode(Stack* stack);

/**
*   @brief Функция UnitTest проводит тестирование стака.
*/
int UnitTest ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
