#ifndef ERRORS_H
#define ERRORS_H
/**
*   @file
*   @brief Файл содержит в себе описания машинных кодов команд, тип численных аргументов команд и точность для сравнения.
*/

#include "../libs/stack/stack.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define COMMENT_SYMBOL ';'
#define MAX_CMD_LEN 32
#define SIGNATURE 'WOEM'
#define CC_VERSION 2.1
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum COMMAND_MACHINE_CODES
{
  #define DEF_COMMAND(enum_name, n_args, id, ...)  \
    enum_name = id,                                \

  #include "../defines_and_setups/commands_defenitions.h"

  #undef DEF_COMMAND
  #undef DEF_COMMAND_ARG

};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef stack_type arg_t;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#endif
