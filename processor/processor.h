#ifndef _PROCESSOR_
#define _PROCESSOR_

#include "../Commands.h"

#define JUMP(COMPARISON_SIGN)                                                  \
do{                                                                            \
    arg1 = StackPop(&spu->stk);                                                \
    arg2 = StackPop(&spu->stk);                                                \
    if (arg2 COMPARISON_SIGN arg1)                                             \
    {                                                                          \
        spu->ip = spu->code[spu->ip + CMD_SHIFT] - CMD_SHIFT;                  \
    }                                                                          \
    spu->ip++;                                                                 \
    break;                                                                     \
}                                                                              \
while(0)

#define REGS(NAME_REGISTER)                                                    \
do{                                                                            \
    if (reg == NAME_REGISTER)                                                  \
    {                                                                          \
    data[NAME_REGISTER * (- 1) - 1] += StackPop(&spu->stk);                    \
    printf("data[%s]: %lg\n", #NAME_REGISTER, data[NAME_REGISTER * (- 1) - 1]); \
    return NAME_REGISTER;                                                      \
    }                                                                          \
}                                                                              \
while(0)

#define WHAT_IS_REG(COMMAND_ENUM)             \
do{                                           \
    ip_register = COMMAND_ENUM * (- 1) - 1;        \
}                     \
while(0)

#define WHAT_IS_OPER(OPERATOR)             \
do{                                           \
    spu->ip++;          \
    printf("\nGEGEGE register = %lg ++++ num = %d\n\n", spu->registers[ip_register], spu->code[spu->ip]);\
    StackPush(&spu->stk, spu->registers[ip_register] OPERATOR spu->code[spu->ip]);        \
}                     \
while(0)

static const char* BYTE_CODE_R = "../byte_code.txt";

const int NUM_REGISTERS = 5;

enum consts
{
    CMD_SHIFT  = 1,
    ARG_SHIFT  = 2,
};

struct spu_t
{
    stack_t stk;
    int     ip;
    double* registers;
    int*    code;
    int     code_elems;
};

regs PushRegister  (struct spu_t* spu, double* data, int reg);

void InitStat      (struct stat* commands);
void SpuDtor       (struct spu_t* spu);
void ReadByteFile  (struct spu_t* spu);
void LaunchCommand (struct spu_t* spu);
void UniversalPush (struct spu_t* spu);
void SpuCtor       (struct spu_t* spu, struct stat* commands);
void FillingCode   (struct spu_t* spu, FILE* mach_code_read);

#endif
