#ifndef ASM_H
#define ASM_H
/**
*   @file
*   @brief Файл содержит в себе прототипы функций для процессорного ассемблера.
*/
#include "../onegin_proc/onegin.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define PROC_COMMENT_SYMBOL ';'

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

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmCheckCommand реализует проверку команды на правильность.
*   
*   @param [in] command_and_args Указатель на строку, которая хранит в себе команду и аргументы.
*   @param [in] command_name Указатель на строку, которая хранит в себе слово команды.
*   @param [in] command_len Длина слова команды.
*   
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmCheckCommand (const char* command_and_args, const char* command_name, int command_len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmCheckCmdEnd проверяет конец слова команды (текста команды или аргументов) на правильность.
*   
*   @param [in] command_and_args Указатель на строку, которая хранит в себе слово команды.
*   
*   @return 0, если что-то не так, иначе 1.
*/
int AsmCheckCmdEnd (const char* command_and_args);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmParseCommand реализует ассемблирование команды.
*   
*   @param [in] cmd_array Массив с машинными кодами команд.
*   @param [in] command_and_args Указатель на строку, которая хранит в себе команду и аргументы.
*   @param [in] programm_counter Указатель на положение следующего места для записи машинной команды.
*   @param [in] listing_f Указатель на структуру #FILE для записи лога компиляции.
*   
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmParseCommand (void* cmd_array, char* command_and_args, int* pc, FILE* listing_f);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmOpenFile открывает файл и делает дополнительные проверки.
*   
*   @param [in] filename Имя файла для открытия.
*   @param [in] mode Режим открытия файла.
*   
*   @return Указатель на структуру #FILE
*/
FILE* AsmOpenFile (const char* filename, const char* mode);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmPreprocStrArray проводит препроцессинг массива строк с командами.
*   
*   @param [in] str_array Указатель на массив строк, который хранит в себе команды и аргументы.
*   @param [in] num_lines  Количество строк с командами, т.е. размер массива #str_array.
* 
*   @return  Один из кодов #AsmReturnCodes.
*/
int AsmPreprocStrArray (char** str_array, size_t num_lines);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmProcessFile реализует ассемблирование файла.
*   
*   @param [in] filename_to_read Имя файла для чтения.
*   @param [in] filename_to_write Имя файла для записи.
*   @param [in] filename_listing Имя файла для записи листинга компиляции.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmProcessFile(const char* filename_to_read, const char* filename_to_write, const char* filename_listing);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmFindCmdArraySize находит размер для массива команд.
*   
*   @param [in] str_array Указатель на массив строк, который хранит в себе команды и аргументы.
*   @param [in] num_lines Количество строк с командами, т.е. размер массива #str_array.
* 
*   @return Количество байт для аллоцирования массива.
*/
ssize_t AsmFindCmdArraySize (char** str_array, size_t num_lines);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmPprintArgLst красиво печает аргуемент команды в файл листинга.
*   
*   @param [in] file Указатель на структуру #FILE с листингом компиляции.
*   @param [in] val Указатель на значение для печати
*   @param [in] el_size Размер типа значения
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmPprintArgLst (FILE* file, void* val, size_t el_size);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Функция AsmUnitTest тестирует ассемблирование.
* 
*   @return Один из кодов #AsmReturnCodes.
*/
int AsmUnitTest ();

#endif