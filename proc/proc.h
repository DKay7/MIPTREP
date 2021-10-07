/**
*   @file
*   @brief Файл содержит в себе прототипы функций для основы процессора.
*/

#include "stack.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Малая величина для сравнения чисел с плавающей точкой с нулем.
#define EPSILON 1e-5

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

///Определение типа данных, с которыми работает процессор.
typedef double stack_type;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Перечисление кодов ошибок, которые функции процессора возвращают.  
*/
enum AsmReturnCodes
{
    PROC_OK = 0x00000001,
    PROC_NOT_ENOUGH_VALUES_IN_STACK = 0x00000002,
    PROC_ZERO_DIVISION_ERR = 0x00000004,
    PROC_INTERNAL_STACK_ERR = 0x00000008,
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
