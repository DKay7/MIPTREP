#define REG_SIZE 4
#define RAM_SIZE 131072
#define STACK_INIT_SIZE 16

enum CpuRegisters
{
    #define DEF_REGISTER(enum_name, ...)  \
        enum_name,                        \
    
    #include "registers_defenitions.h"

    #undef DEF_REGISTER
};

enum ByteMasks
{   
    OPTIONAL_ARG        = 0x01,
    IMMEDIATE_CONST     = 0x20,
    REGISTER_VALUE      = 0x40,
    RAM_VALUE           = 0x80,
};