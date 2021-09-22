/**
*   @file
*   @brief Файл содержит в себе прототипы функций для работы со стаком и саму структуру стака.
*/

#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define STACK_DUMP (stack) StackDumpFunction (stack, __LINE__, __FUNCTION__, __FILE__, #stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Объявление типа стака. Необходимо, чтобы стак был независим от типа данных.
typedef int stack_type;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct Stack
{
    stack_type* data;
    size_t size;
    size_t capacity;
    int error_code;
} Srack;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Перечисление кодов ошибок, которые функции работы со стаком возвращают.  
*/
enum RETURN_CODES
{
    STACK_OK =              0x00000000,     // Все ОК.
    STACK_MEM_ALLOCK_ERR =  0x00000001,     // Ошибка аллоцирования / реаллоцирования памяти.
    STACK_INCREASE_ERR =    0x00000002,     // Ошибка в функции увеличения размера стека.
    STACK_DECREASE_ERR =    0x00000003      // Ошибка в функции уменьшения размера стека.
};

/**
*   Перечисление функций для отладки.  
*/
enum RETURN_CODES
{
    STACK_CTOR  =           0x00000100,
    STACK_DTOR =            0x00000200,
    STACK_PUSH =            0x00000300,
    STACK_POP =             0x00000400,
    STACK_INCREASE =        0x00000500,
    STACK_DECREASE =        0x00000600,
    STACK_DUMPFUNCTION =    0x00000700,
    UNIT_TEST =             0x00000800
};

/**
*   Перечисление отравляющих констант.  
*/
enum POISONS
{
    STACK_DATA_POISON = 0xffffffff // Отравление данных.
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackCtor конструирует объект стака.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @param [in] size Начальный размер для аллоцирования буффера.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackCtor (Stack* stack, int size);

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
*   @param [in] line Номер строки, в которой вызвана данная функция.
*   @param [in] func_name Имя функции, в которой вызвана данная функция.
*   @param [in] file_name Имя файла, из которого вызвана данная функция.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackDumpFunction (Stack* stack, int line, char* func_name, char* file_name, char* stack_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackValidate проверяет, что со стеком все хорошо.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackValidateFunc (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция UnitTest проводит тестирование стака.
*   
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*/
int UnitTest (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
