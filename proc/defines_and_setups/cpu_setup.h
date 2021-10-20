
#define REG_SIZE 4
#define RAM_SIZE 32
#define STACK_INIT_SIZE 16


enum CpuRegisters
{
    #define DEF_REGISER(enum_name, id, str_name, ...)  \
        enum_name = id,                                \
    
    #include "registers_defenitions.h"

    #undef DEF_REGISER
};

enum ByteMasks
{
    IMMEDIATE_CONST     = 0x20,
    IMMEDIATE_CONST_LOW = 0x01,

    REGISTER_VALUE      = 0x40,
    REGISTER_VALUE_LOW  = 0x02,

    RAM_VALUE           = 0x80,
    RAM_VALUE_LOW       = 0x04,

};