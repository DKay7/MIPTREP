#ifndef PROC_H
#define PROC_H
/**
*   @file
*   @brief Файл содержит в себе прототипы функций для основы процессора.
*/

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#include "../stack_proc/stack.h"
#include "proc_errors.h"
#include "cmd_setup.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Количество регистров массива
#define REG_SIZE 4

/// Объем оперативной памяти массива
#define MEM_SIZE 256

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/** @struct AdditionalInfo
*  @brief Дополнительные данные стека.
*/
typedef struct
{
  Stack* stack;         /**< Поле Cpu#stack хранит указатель на стек процессора. */
  void* cmd_array;      /**< Поле Cpu#cmd_array хранит указатель на бинарный массив команд. */
  int pc;               /**< Поле Cpu#pc хранит указатель на текущую команду в массиве команд */
  arg_t regs[REG_SIZE]; /**< Поле Cpu#regs массив регистров процессора*/
  arg_t mem[MEM_SIZE];  /**< Поле Cpu#mem оперативная память регистра*/
} Cpu;

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