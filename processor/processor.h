#ifndef _PROCESSOR_
#define _PROCESSOR_

#define JUMP(COMPARISON_SIGN)                                        \
do{                                                                  \
    arg1 = StackPop(&spu->stk);                                      \
    arg2 = StackPop(&spu->stk);                                      \
    if (arg2 COMPARISON_SIGN arg1)                                   \
    {                                                                \
        spu->ip = spu->code[spu->ip + COMMAND_ARGS] - COMMAND_SHIFT; \
    }                                                                \
    spu->ip++;                                                       \
    break;                                                           \
}                                                                    \
while(0)

#define REGS(NAME_REGISTER)                                          \
do{                                                                  \
    data[NAME_REGISTER * (- 1) - 1]++;                               \
    printf("data: %d\n", data[NAME_REGISTER * (- 1) - 1]);           \
    break;                                                           \
}                                                                    \
while(0)

static const char* BYTE_CODE_R = "../byte_code.txt";

const int NUM_REGISTERS = 5;

enum consts
{
    COMMAND_SHIFT = 1,
    COMMAND_ARGS  = 1,
};

struct spu_t
{
    struct stack_t stk;
    int ip;
    int* registers;
    int* code;
    int code_elems;
};

void PushRegister  (int* data, int reg);
void InitStat      (struct stat* commands);
void SpuDtor       (struct spu_t* spu);
void ReadByteFile  (struct spu_t* spu);
void LaunchCommand (struct spu_t* spu);
void SpuCtor       (struct spu_t* spu, struct stat* commands);
void FillingCode   (struct spu_t* spu, FILE* mach_code_read);

#endif
