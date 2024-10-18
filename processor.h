#ifndef PROCESSOR
#define PROCESSOR

const int NUM_REGISTERS = 5;

struct spu_t
{
    struct stack_t stk;
    int ip;
    int* registers;
    int* code;
};

enum comands
{
    CMD_HLT  = 0,
    CMD_PUSH = 1,
    CMD_SUB  = 2,
    CMD_DIV  = 3,
    CMD_ADD  = 4,
    CMD_MUL  = 5,
    CMD_OUT  = 6,
    CMD_IN   = 7,
    CMD_SQRT = 8,
    CMD_SIN  = 9,
    CMD_COS  = 10,
    CMD_DUMP = 11,
    CMD_JUMP = 12,
    CMD_JB   = 13,
    CMD_JBE  = 14,
};

enum registers
{
    JUMPS = 0,
};

#endif
