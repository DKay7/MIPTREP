#ifndef DEF_REGISTER
#define DEF_REGISTER(...)
#endif

DEF_REGISTER (AX, 0x000, "ax")
DEF_REGISTER (BX, 0x001, "bx")
DEF_REGISTER (CX, 0x002, "cx")
DEF_REGISTER (DX, 0x003, "dx")


#ifdef DEF_REGISTER
#undef DEF_REGISTER
#endif
