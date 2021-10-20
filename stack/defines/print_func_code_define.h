#define DEF_FUNC_CODE(enum_name, id, text) \
    if (func_code & id)                    \
    {                                      \
        printf (RED_COLOR(text));          \
        func_code -= id;                   \
    }                                      \


#include "func_code_defines.h"

#undef DEF_FUNC_CODE