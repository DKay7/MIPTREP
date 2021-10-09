/**
*   @file
*   @brief Файл содержит в себе прототипы функций для основы процессора.
*/

#include "stack_proc/stack.h"
#include "onegin_proc/onegin.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


/// Малая величина для сравнения чисел с плавающей точкой с нулем.
#ifndef EPSILON
#define EPSILON 1e-5
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#ifdef STACK_DATA_POISON
#undef STACK_DATA_POISON
#define STACK_DATA_POISON 666.666
#else
#define STACK_DATA_POISON 666.666
#endif

/// Спецификатор ввода/вывода для типа данных #stack_type
#ifdef STACK_TYPE_SPEC
#undef STACK_TYPE_SPEC
#define STACK_TYPE_SPEC "%lf "
#else
#define STACK_TYPE_SPEC "%lf "
#endif

/// Макрос для проверки количества аргументов команды
#ifndef CHECK_ARGS_NUM
#define CHECK_ARGS_NUM(actual_num, correct_num) \
do { \
    if (actual_num != correct_num)  \
    {   \
        errno = errno | PROC_WRONG_NUM_OF_CMD_ARGS; \
        return errno;   \
    }   \
} while (0)
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

///Определение типа данных, с которыми работает процессор.
//typedef double stack_type;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Перечисление кодов ошибок, которые функции процессора возвращают.  
*/
enum AsmReturnCodes
{
    PROC_OK =                           0x00000000,
    PROC_NOT_ENOUGH_VALUES_IN_STACK =   0x00000001,
    PROC_ZERO_DIVISION_ERR =            0x00000002,
    PROC_INTERNAL_STACK_ERR =           0x00000004,
    PROC_ERR_READING_CMD_NAME =         0x00000008,
    PROC_WRONG_NUM_OF_CMD_ARGS =        0x00000010,
    PROC_FILE_OPENING_ERR =             0x00000020,
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Константа для хранения ошибки процессора. 
extern int errno;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmPush реализует операцию push.
*   
*   @param [in, out] stack Указатель на структуру  #Stack.
*   @param [in] value Значение для пуша в стек процессора.
*
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmPush (Stack* stack, stack_type value);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmPop реализует операцию pop.
*   
*   @param [in, out] stack Указатель на структуру  #Stack.
*   @param [out] value Указатель на переменную для записи значения.
*
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmPop (Stack* stack, stack_type* value);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmAdd реализует операцию add.
*   
*   @param [in, out] stack Указатель на структуру  #Stack.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmAdd (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


/**
*   Функция AsmSub реализует операцию sub.
*   
*   @param [in, out] stack Указатель на структуру  #Stack.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmSub (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmAdd реализует операцию mul.
*   
*   @param [in, out] stack Указатель на структуру #Stack.
*
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmMul (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmAdd реализует операцию add.
*   
*   @param [in, out] stack Указатель на структуру  #Stack.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmDiv (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmParseCommand реализует парсинг команды.
*   
*   @param [in, out] stack Указатель на структуру  #Stack.
*   @param [in] command_and_args Указатель на структуру #String, которая хранит в себе команду и аргументы.
*   
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmParseCommand(Stack* stack, String* command_and_args);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmProcessFile реализует парсинг файла.
*   
*   @param [in, out] stack Указатель на структуру  #Stack.
*   @param [in] file Файдловый дескриптор для чтения.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmProcessFile(Stack* stack, FILE* file);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция ProcDump выводит отладочную информацию о процессоре.
*   
*   @param [in] stack Указатель на структуру  #Stack.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int ProcDump (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция ProcValidate проверяет, что с процессором все хорошо.
*   
*   @param [in] stack Указатель на структуру  #Stack.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int ProcValidate (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция ProcUnitTest тестирует процессор.
*   
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int ProcUnitTest();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
