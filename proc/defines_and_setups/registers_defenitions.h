#ifndef DEF_REGISTER
#define DEF_REGISTER(...)
#endif

DEF_REGISTER (AX, "ax")
DEF_REGISTER (BX, "bx")
DEF_REGISTER (CX, "cx")
DEF_REGISTER (DX, "dx")


#ifdef DEF_REGISTER
#undef DEF_REGISTER
#endif
