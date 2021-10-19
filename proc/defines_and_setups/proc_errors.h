#ifndef PROC_ERRORS_H
#define PROC_ERRORS_H
/**
*   @file
*   @brief Файл содержит в себе описания кодов ошибок и переменную #proc_errno.
*/

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
    PROC_UNKNOWN_CMD_ERR            = 0x08,
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum AsmCCReturnCodes
{
    ASMCC_OK                        = 0x00,
    ASMCC_INVALID_COMMAND           = 0x01,
    ASMCC_ERR_READING_CMD_NAME      = 0x02,
    ASMCC_ERR_READING_CMD_ARGS      = 0x04,
    ASMCC_WRONG_NUM_OF_CMD_ARGS     = 0x08,
    ASMCC_FILE_OPENING_ERR          = 0x10,
    ASMCC_ERR_ALLOCATING_MEMORY     = 0x20,
    ASMCC_ERR_OPENING_FILE          = 0x04,
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int proc_errno = PROC_OK;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#endif