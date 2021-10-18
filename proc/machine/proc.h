#ifndef PROC_H
#define PROC_H
/**
*   @file
*   @brief Файл содержит в себе прототипы функций для основы процессора.
*/

#include "../stack_proc/stack.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Малая величина для сравнения чисел с плавающей точкой с нулем.
#ifndef EPSILON
#define EPSILON 1e-5
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum COMMAND_MACHINE_CODES
{
  #define DEF_COMMAND(name, n_args, id, ...) \
    name = id, \

  #include "../commands.h"

  #undef DEF_COMMAND
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Перечисление кодов ошибок, которые функции процессора возвращают.  
*/
enum ProcReturnCodes
{
    PROC_OK                         = 0x00,
    PROC_NOT_ENOUGH_VALUES_IN_STACK = 0x01,
    PROC_ZERO_DIVISION_ERR          = 0x02,
    PROC_INTERNAL_STACK_ERR         = 0x04,
    ASM_ERR_READING_CMD_NAME        = 0x08,
    ASM_WRONG_NUM_OF_CMD_ARGS       = 0x10,
    ASM_FILE_OPENING_ERR            = 0x20,
    ASM_ERR_ALLOCATING_MEMORY       = 0x40,
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Константа для хранения ошибки процессора. 
int proc_errno = PROC_OK;

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
#endif