#ifndef _COMPILE_COMMANDS_
#define _COMPILE_COMMANDS_

#define COMPILATION(COMMAND_NAME, COMMAND_ENUM)                                      \
{                                                                                    \
    if (strcmp((const char*)assm->command, COMMAND_NAME) == 0)                       \
    {                                                                                \
        assm->num_elem_file++;                                                       \
        fprintf(assm->byte_code_write, "%d ", COMMAND_ENUM);                         \
        assm->last_command = COMMAND_ENUM;                                           \
        CheckArg(assm);                                                              \
        free(assm->command);                                                         \
        checker = 1;                                                                 \
        continue;                                                                    \
    }                                                                                \
}

#define REGS(COMMAND_NAME, COMMAND_ENUM)                                             \
{                                                                                    \
    if (strcmp((const char*)assm->command, COMMAND_NAME) == 0){return COMMAND_ENUM;} \
}

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
    PUSHR = 15,
};

enum regs
{
    AX = - 1,
    BX = - 2,
    CX = - 3,
    DX = - 4,
};

const int INT_ARG      = 100;
const int NUM_REGS     = 4;
const int SIZE_REG     = 4;  // 2 symbols of register + \n + \r
const int SIZE_LABEL   = 10;
const int COMMAND_SIZE = 10;

void CheckArg      (struct assembler* assm);
void UniversalPush (struct assembler* assm);
void WriteCommand  (struct assembler* assm);
void SkipSpaces    (struct assembler* assm, int symbol0, int symbol1);
//void WhatIsArg(struct assm* global_assm);

#endif
