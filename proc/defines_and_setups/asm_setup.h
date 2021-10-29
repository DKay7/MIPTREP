#ifndef ERRORS_H
#define ERRORS_H
/**
*   @file
*   @brief Файл содержит в себе описания машинных кодов команд, тип численных аргументов команд и точность для сравнения.
*/

#include "../libs/stack/stack.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define COMMENT_SYMBOL ';'
#define MAX_CMD_LEN 64
#define SIGNATURE 'WOEM'
#define CC_VERSION 2.1

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum COMMAND_MACHINE_CODES
{
  #define DEF_COMMAND(enum_name, ...)  \
    enum_name,                         \

  #include "../defines_and_setups/commands_defenitions.h"

  #undef DEF_COMMAND
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef double arg_t;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#endif
