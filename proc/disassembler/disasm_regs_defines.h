#include "../defines_and_setups/cpu_setup.h"

#define DEF_REGISTER(enum_name, str_name, ...)          \
    case enum_name:                                     \
        DisAsmWriteOutput (adc, "%s", str_name);        \
        break;


switch (adc->cmd_array[adc->ip + sizeof (unsigned char)])
{
    #include "../defines_and_setups/registers_defenitions.h"
}

#undef DEF_REGISTER
