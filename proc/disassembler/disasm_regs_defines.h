#define DEF_REGISTER(enum_name, id, str_name, ...)      \
    case id:                                            \
        DisAsmWriteOutput (adc, "%s", str_name);        \
        break;                                          \


switch (adc->cmd_array[adc->ip + sizeof (unsigned char)])
{
    #include "../defines_and_setups/registers_defenitions.h"
}

#undef DEF_REGISTER
