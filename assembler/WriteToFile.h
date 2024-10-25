#ifndef WRITE_TO_FILE
#define WRITE_TO_FILE

#define COMPILATION(COMMAND_NAME, COMMAND_ENUM)                                        \
{                                                                                   \
    if (strcmp((const char*)global_assm->command, COMMAND_NAME) == 0)                         \
    {                                                                                  \
        printf("\ni am in compilation (if)\n");                                        \
        number_command++;                                                              \
        fprintf(global_assm->byte_code_write, "%d\n", COMMAND_ENUM);                          \
        continue;                                                                      \
    }                                                                                   \
}

#define COMPILATION_ARG(COMMAND_NAME, COMMAND_ENUM)                                    \
{                                                                                      \
    if (strcmp((const char*)global_assm->command, COMMAND_NAME) == 0)                         \
    {                                                                                  \
        printf("\ni am in compilation_ARG\n");                                         \
        fscanf(global_assm->commands_file, "%d", &arg);                                       \
        number_command += 2;                                                           \
        fprintf(global_assm->byte_code_write, "%d %d\n", COMMAND_ENUM, arg);                  \
        continue;                                                                      \
    }                                                                                  \
} //TODO use func check args

//TODO убрать этот дефайн
#define COMPILATION_JMP(COMMAND_NAME, COMMAND_ENUM)                                    \
{                                                                                      \
    if (strcmp((const char*)global_assm->command, COMMAND_NAME) == 0)                         \
    {                                                                                  \
        printf("\ni am in compilation_JMP\n");                                         \
        fscanf(global_assm->commands_file, "%s", jmp_arg);                                    \
        number_command += 2;                                                           \
                                                                                       \
        assert(jmp_arg);                                                               \
                                                                                       \
        FindMark(global_assm, COMMAND_ENUM);                                 \
        continue;                                                                      \
    }                                                                                  \
}
//TODO убрать копипаст
#define COMPILATION_REGS(COMMAND_NAME, COMMAND_ENUM)                                   \
{                                                                                      \
    if (strcmp((const char*)global_assm->command, COMMAND_NAME) == 0)                         \
    {                                                                                  \
        printf("\ni am in compilation_REGS\n");                                        \
        int reg = DefineReg(global_assm);                                                     \
        if (reg >= - NUM_REGS){                                                        \
        number_command += 2;                                                           \
        fprintf(global_assm->byte_code_write, "%d %d\n", COMMAND_ENUM, reg);}                 \
        continue;                                                                      \
    }                                                                                  \
}

#define REGS(COMMAND_NAME, COMMAND_ENUM)                                     \
{                                                                          \
    if (strcmp((const char*)reg, COMMAND_NAME) == 0){return COMMAND_ENUM;}   \
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
    AX       = - 1,
    BX       = - 2,
    CX       = - 3,
    DX       = - 4,
};

const int NUM_REGS = 4;
const int SIZE_REG = 4;
const int SIZE_LABEL = 10;

#endif
