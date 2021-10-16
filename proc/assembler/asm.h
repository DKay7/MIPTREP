#ifndef ASM_H
#define ASM_H
/**
*   @file
*   @brief Файл содержит в себе прототипы функций для процессорного ассемблера.
*/
#include "../onegin_proc/onegin.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Макрос для проверки количества аргументов команды
#define CHECK_ARGS_NUM(actual_num, correct_num) \
do { \
    if (actual_num != correct_num)  \
    {   \
        proc_errno = proc_errno | ASM_WRONG_NUM_OF_CMD_ARGS; \
        return proc_errno;   \
    }   \
} while (0)

/**
*   Функция AsmParseCommand реализует ассемблирование команды.
*   
*   @param [in] command_and_args Указатель на структуру #String, которая хранит в себе команду и аргументы.
*   
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmParseCommand(double* cmd_array, String* command_and_args, int* programm_counter);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmProcessFile реализует ассемблирование файла.
*   
*   @param [in] file Файдловый дескриптор для чтения.
*   @param [in] filename_to_write Имя файла для записи.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmProcessFile(FILE* file, const char* filename_to_write);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmUnitTest тестирует ассемблирование.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmUnitTest ();

#endif