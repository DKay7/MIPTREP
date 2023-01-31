#ifndef DEF_REGISTER
#define DEF_REGISTER(...)
#endif

DEF_REGISTER (AX, "ax")
DEF_REGISTER (BX, "bx")
DEF_REGISTER (CX, "cx")
DEF_REGISTER (DX, "dx")
DEF_REGISTER (EX, "ex")
DEF_REGISTER (FX, "fx")
DEF_REGISTER (GX, "gx")
DEF_REGISTER (HX, "hx")
DEF_REGISTER (IX, "ix")
DEF_REGISTER (JX, "jx")
DEF_REGISTER (KX, "kx")
DEF_REGISTER (LX, "lx")
DEF_REGISTER (MX, "mx")
DEF_REGISTER (NX, "nx")
DEF_REGISTER (OX, "ox")
DEF_REGISTER (PX, "px")
DEF_REGISTER (QX, "qx")
DEF_REGISTER (RX, "rx")
DEF_REGISTER (SX, "sx")
DEF_REGISTER (TX, "tx")
DEF_REGISTER (XX, "xx")
DEF_REGISTER (YX, "yx")
DEF_REGISTER (TMPX, "tmpx")
DEF_REGISTER (RETX, "retx")


#ifdef DEF_REGISTER
#undef DEF_REGISTER
#endif
