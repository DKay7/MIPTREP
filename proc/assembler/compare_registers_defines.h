#include "../defines_and_setups/cpu_setup.h"

#define DEF_REGISTER(enum_name, str_name, ...)                                      \
    if (strcmp (reg_arg, str_name) == 0)                                            \
    {                                                                               \
        arg_t arg = enum_name;                                                      \
        *(arg_t*) &(acc->cmd_array[acc->ip])  = arg;                                \
        acc->ip +=  sizeof (arg_t);                                                 \
        PrintValToListing (listing_file, &arg, sizeof (arg_t));                     \
    }                                                                               \
    else                                                                            \

#include "../defines_and_setups/registers_defenitions.h"

/*else*/
{
    acc->asm_errno |= ASMCC_UNKNOWN_REG_NAME_ERR;
}

#undef DEF_REGISTER
