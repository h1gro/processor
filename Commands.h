#ifndef _COMMANDS_
#define _COMMANDS_

enum comands
{
    HLT        = 0,
    PUSH       = 1,
    SUB        = 2,
    DIV        = 3,
    ADD        = 4,
    MUL        = 5,
    OUT        = 6,
    IN         = 7,
    SQRT       = 8,
    SIN        = 9,
    COS        = 10,
    DUMP       = 11,
    JUMP       = 12,
    JB         = 13,
    JBE        = 14,
    JA         = 15,
    JAE        = 16,
    SSQRT      = 17,
};

enum regs
{
    AX = -1,
    BX = -2,
    CX = -3,
    DX = -4,
};

enum encodings
{
    CMD_STACK_PUSH   = 0,
    CMD_REG_PUSH     = 1,
    CMD_REG_TO_STACK = 2,
};

/*              Encoding Instrations:
machine code for push in 2 arguments:
[1] [number]
example: push -245 --> 1 -245

machine code for push in 3 arguments:
[1] [0 or 1 (enum)] [(int arg - it's number) or (-1, -2, -3, -4 - it's registers)]
example: push bx --> 1 1 -1

machine code for push in 4 arguments:
[1] [0 or 1 or 2 (enum)] [reg -1, -2, -3, -4] [oper add, sub, ...] [number]
example: push cx-4 --> 1 2 -3 2 4*/

#endif
