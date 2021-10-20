#define DEF_REGISTER(enum_name, id, str_name, ...)      \
    if (strcmp (reg_arg, str_name) == 0)                \
    {                                                   \
        acc->cmd_array[acc->ip] = (unsigned char) id;   \
        acc->ip += sizeof (unsigned char);              \
        fprintf (listing_file, "%-23X", id);            \
    } else                                              \

#include "../defines_and_setups/registers_defenitions.h"

/*else*/
{
    acc->asm_errno |= ASMCC_UNKNOWN_REG_NAME_ERR;
}

#undef DEF_REGISTER
