#ifndef _COMMANDS_
#define _COMMANDS_

enum comands
{
    HLT   = 0,
    PUSH  = 1,
    SUB   = 2,
    DIV   = 3,
    ADD   = 4,
    MUL   = 5,
    OUT   = 6,
    IN    = 7,
    SQRT  = 8,
    SIN   = 9,
    COS   = 10,
    DUMP  = 11,
    JUMP  = 12,
    JB    = 13,
    JBE   = 14,
    JA    = 15,
    JAE   = 16,
    PUSHR = 17,
};

enum regs
{
    AX = -1,
    BX = -2,
    CX = -3,
    DX = -4,
};

#endif
