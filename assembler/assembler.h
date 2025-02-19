#ifndef _ASSEMBLER_
#define _ASSEMBLER_

#include "../Commands.h"

#define COMPILATION(COMMAND_ENUM)                                                         \
{                                                                                         \
    if (strcasecmp((const char*)assm->command, #COMMAND_ENUM) == 0)                       \
    {                                                                                     \
        assm->num_elem_file++;                                                            \
        fprintf(assm->byte_code_write, "%d ", COMMAND_ENUM);                              \
        assm->last_command = COMMAND_ENUM;                                                \
        free(assm->command);                                                              \
        CheckArg(assm);                                                                   \
        continue;                                                                         \
    }                                                                                     \
}

#define REGS(COMMAND_ENUM)                                                                \
do{                                                                                       \
    if (strcasecmp((const char*)assm->command, #COMMAND_ENUM) == 0){return COMMAND_ENUM;} \
}                                                                                         \
while(0)

const int MAX_SIZE_COM     = 15;
const int NUMBER_OF_LABELS = 10;
const int NO_REGS          = 69;
const int NUM_REGS         = 4;
const int SIZE_REG         = 4;  // 2 symbols of register + \n + \r
const int SIZE_LABEL       = 10;
const int COMMAND_SIZE     = 10;
const int INVALID_ADDR     = -1;
const int NULL_ADDR        = 0;
const int YARLY_ADDR       = -153;

enum push_args
{
    INT_ARG      = 100,
    OPER_ARG     = 200,
    NOT_OPER_ARG = 300,
    MEMORY_PUSH  = 400,
};

enum label_returns
{
    YEARLY_LABEL_ASSIGNED = 90,
    NOT_A_LABEL           = 91,
    NEW_LABEL_ASSIGNED    = 92,
};

enum funcs
{
    CTOR = 89,
    DTOR = 99,
};

struct label
{
    int   addr;
    char* label;
};

struct assembler
{
    FILE* commands_file;
    FILE* byte_code_write;
    char* command;
    char* input_code;
    int   index;
    int   cmd_size;
    int   capacity;
    int   last_command;
    int   num_elem_file;
    label labels[NUMBER_OF_LABELS];
};

int  DefineReg           (struct assembler* assm);
int CheckRegs            (struct assembler* assm);
int WriteCommand         (struct assembler* assm);
int LabelAssignment      (struct assembler* assm);

void InitStat            (struct stat* st_file);
void CompileCommands     (struct assembler* assm);
void CheckArg            (struct assembler* assm);
void UniversalPush       (struct assembler* assm);
void LabelsCtor          (struct assembler* assm);
void LabelsDtor          (struct assembler* assm);
void StructAssmDtor      (struct assembler* assm);
void FindLabel           (struct assembler* assm);
void StructAssmCtor      (struct assembler* assm, struct stat* st_file);
void SkipSpaces          (struct assembler* assm, int symbol0, int symbol1);
void FillingStructLabels (struct assembler* assm, int poison, funcs func_call);

#endif
