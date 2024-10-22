#ifndef ASSEMBLER
#define ASSEMBLER

const int MAX_SIZE_COM    = 15;
const int NUMBER_OF_MARKS = 100;

struct label
{
    int addr;
    char* mark;
};

#define COMPILATION(COMMAND_NAME, COMMAND_ENUM)                                        \
{                                                                                      \
    if (strcmp((const char*)file->command, COMMAND_NAME) == 0)                         \
    {                                                                                  \
        printf("\ni am in compilation (if)\n");                                        \
        number_command++;                                                              \
        fprintf(file->byte_code_write, "%d\n", COMMAND_ENUM);                          \
        continue;                                                                      \
    }                                                                                  \
                                                                                       \
    else if(strchr((const char*)file->command, ':') != NULL)                           \
    {                                                                                  \
        printf("\ni am in compilation (else if)\n");                                   \
        labels[ip_mark].addr = number_command;                                         \
        labels[ip_mark].mark = file->command;                                          \
        printf("ip_mark = %d, addr = %d, mark = %s\n",                                 \
                ip_mark, labels[ip_mark].addr, labels[ip_mark].mark);                  \
        number_command++;                                                              \
        ip_mark++;                                                                     \
        continue;                                                                      \
    }                                                                                  \
}

#define COMPILATION_ARG(COMMAND_NAME, COMMAND_ENUM)                                    \
{                                                                                      \
    if (strcmp((const char*)file->command, COMMAND_NAME) == 0)                         \
    {                                                                                  \
        printf("\ni am in compilation_ARG\n");                                         \
        fscanf(file->commands_file, "%d", &arg);                                       \
        number_command += 2;                                                           \
        fprintf(file->byte_code_write, "%d %d\n", COMMAND_ENUM, arg);                  \
        continue;                                                                      \
    }                                                                                  \
} //TODO use func check args

#define COMPILATION_JMP(COMMAND_NAME, COMMAND_ENUM)                                    \
{                                                                                      \
    if (strcmp((const char*)file->command, COMMAND_NAME) == 0)                         \
    {                                                                                  \
        printf("\ni am in compilation_JMP\n");                                         \
        fscanf(file->commands_file, "%s", str_arg);                                    \
        number_command += 2;                                                           \
                                                                                       \
        assert(str_arg);                                                               \
                                                                                       \
        FindMark(labels, file, COMMAND_ENUM, ip_mark);                                 \
        continue;                                                                      \
    }                                                                                  \
}

#define COMPILATION_REGS(COMMAND_NAME, COMMAND_ENUM)                                   \
{                                                                                      \
    if (strcmp((const char*)file->command, COMMAND_NAME) == 0)                         \
    {                                                                                  \
        printf("\ni am in compilation_REGS\n");                                        \
        int reg = WhatIsReg(file);                                                     \
        if (reg >= - NUM_REGS){                                                        \
        number_command += 2;                                                           \
        fprintf(file->byte_code_write, "%d %d\n", COMMAND_ENUM, reg);}                 \
        continue;                                                                      \
    }                                                                                  \
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
    NUM_REGS =   4,
    SIZE_REG =   4,
};

struct file_t
{
    FILE *commands_file;
    FILE *byte_code_write;
    char* command;
};

int WhatIsReg(struct file_t* file);
void WriteToFile(struct file_t* file, struct stat* st_file, struct label* labels);
void StrFilesCtor(struct file_t* file, struct stat* st_file);
void StrFilesDtor(struct file_t* file);
void InitStat(struct stat* st_file);

#endif
