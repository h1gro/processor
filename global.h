#ifndef IFDEF_CONST
#define IFDEF_CONST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_CHECK(stk) (StackCheck(stk, __FILE__, __LINE__, __func__));

//on/off debug mode
#define DEBUG 153.153

#define DUMP_FILE "dump.txt"

#define LEVEL_OF_PROTECTION

#ifdef DEBUG
    #define ON_DEBUG(code)code
    #define INIT(canary, name) canary ,__FILE__, __LINE__, __func__, #name
#else
    #define ON_DEBUG(code)
    #define INIT(name)
#endif

typedef int stackelem_t;

const stackelem_t POISON  = -153;
const stackelem_t CANARY  = 531;
const double EPSILON = 1e-4;

enum errors_t
{
    NO_ERRORS           = 0,
    PUSH_ERROR          = 1,
    POP_ERROR           = 2,
    CTOR_ERROR          = 3,
    STK_ERROR           = 4,
    CAPACITY_ERROR      = 5,
    SIZE_ERROR          = 6,
    CANARY1_BUF_ERROR   = 7,
    CANARY2_BUF_ERROR   = 8,
    CANARY1_STR_ERROR   = 9,
    CANARY2_STR_ERROR   = 10,
    MY_ERROR            = 11
};

enum stack
{
    CAPACITY     = 3,
    CAPAC_RESIZE = 2,
    CAPAC_SHIFT  = 4
};

enum call_funcs
{
    PUSH        = 777,
    POP         = 666,
    INFO_PRINT  = 555,
    ERROR_PRINT = 444,
    RUN         = 333
};

enum canaries
{
    NUM_CANARIES_BUF      = 2,
    NUM_CANARIES_STR      = 2,
    NUM_CANARIES_IN_RIGHT = 1,
    NUM_CANARIES_IN_LEFT  = 1
};

struct stack_t
{
#ifdef DEBUG
    stackelem_t canary1;
    const char* file;
    const int   line;
    const char* func;
    const char* name;
#endif
    stackelem_t *data;
    int size;
    int capacity;
    int error_code;
    FILE *output;
#ifdef DEBUG
    stackelem_t canary2;
#endif
};

int CheckForErrors(struct stack_t *stk);
int StackCheck(struct stack_t *stk, const char* file, int line, const char* func);

void StackCtor(struct stack_t *stk);
void StackDtor(struct stack_t *stk);
void FillingDataPoison(stackelem_t *data, int num_el_poison);
void StackPush(struct stack_t *stk, stackelem_t elem);
void ResizeIf(struct stack_t *stk, int is_pop_or_push);
void StackErrorOutput(struct stack_t *stk);
void StackDump(struct stack_t *stk, const char* func, const char* file, int line, int dump_call);

stackelem_t StackPop(struct stack_t *stk);

#endif
