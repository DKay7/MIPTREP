#ifndef PROC_ERRORS_H
#define PROC_ERRORS_H
/**
*   @file
*   @brief Файл содержит в себе описания кодов ошибок.
*/

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum CpuReturnCodes
{
    #define DEF_ERR_CODE(enum_name, id, text)  \
            enum_name = id,                    \
    
    #include "cpu_errors_defenitions.h"

    #undef DEF_ERR_CODE
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum AsmCCReturnCodes
{
    #define DEF_ERR_CODE(enum_name, id, text)  \
            enum_name = id,                    \
    
    #include "asm_errors_defenitions.h"

    #undef DEF_ERR_CODE
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum DisAsmReturnCodes
{
    #define DEF_ERR_CODE(enum_name, id, text)  \
            enum_name = id,                    \
    
    #include "disasm_errors_defenitions.h"

    #undef DEF_ERR_CODE
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define EPSILON 1e-7

#define CHECK_STACK(cpu, stack_code) {          \
    if (stack_code != STACK_OK)                 \
    {                                           \
        cpu->errno |= CPU_INTERNAL_STACK_ERR;   \
        return cpu->errno;                      \
    }}

#define CHECK_STACK_SIZE(cpu, stack_size, required_stack_size)      \
    if (stack_size < required_stack_size)                          	\
    {                                                              	\
        cpu->errno |= CPU_NOT_ENOUGH_VALUES_IN_STACK; 	   			\
        return cpu->errno;                                    		\
    }

#define CHECK_ZERO_DIVISION(cpu, value)                     \
    if (fabs (value) < EPSILON)                       		\
    {                                                       \
        cpu->errno |= CPU_ZERO_DIVISION_ERR;   			    \
        return cpu->errno;                                  \
    }



#endif