#ifndef READ_BYTE_FILE
#define READ_BYTE_FILE

enum consts
{
    COMMAND_SHIFT = 1,
    COMMAND_ARGS  = 1,
};

enum regs
{
    AX = - 1,
    BX = - 2,
    CX = - 3,
    DX = - 4,
};


//TODO read ABOUT direct # and ##

#define IP_SHIFT(COMPARISON_SIGN)                                    \
do{                                                                  \
    arg1 = StackPop(&spu->stk);                                      \
    arg2 = StackPop(&spu->stk);                                      \
                                                                     \
    if(arg2 COMPARISON_SIGN arg1)                                    \
    {                                                                \
        spu->ip = spu->code[spu->ip + COMMAND_ARGS] - COMMAND_SHIFT; \
    }                                                                \
                                                                     \
    spu->ip++;                                                       \
    break;                                                           \
}while(0)

#define REGS(NAME_REGISTER)                                          \
do{                                                                  \
    data[NAME_REGISTER * (- 1) - 1]++;                               \
    printf("data: %d\n", data[NAME_REGISTER * (- 1) - 1]);           \
}while(0);

void ReadByteFile(struct spu_t* spu);
void FillingCode(struct spu_t* spu, FILE* mach_code_read);
void InitStat(struct stat* commands);
void LaunchCommand(struct spu_t* spu);
void PushRegister(int* data, int reg);

#endif

