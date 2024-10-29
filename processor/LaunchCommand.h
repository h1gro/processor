#ifndef LAUNCH_COMMAND
#define LAUNCH_COMMAND

//TODO read ABOUT direct # and ##

#define JUMP(COMPARISON_SIGN)                                        \
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

void LaunchCommand(struct spu_t* spu);
void PushRegister(int* data, int reg);

#endif
