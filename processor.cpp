#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "global.h"
#include "processor.h"

int CountCommands();

int main()
{
    FILE *mach_code_read = fopen(MACHINE_CODE, "rb");

    int file_size = CountCommands();

    int* code = (int*) calloc(file_size, sizeof(int));
    int num_elements = fread(code, 1, file_size, mach_code_read);

    printf("num_elems = %d, file_size = %d\n", num_elements, file_size);

    assert(num_elements == file_size);
    assert(mach_code_read);

    struct stack_t stk = {INIT(CANARY, stk)};

    StackCtor(&stk);

    while(1)
    {
        int arg1 = 0;
        int cmd = 0;
        fscanf(mach_code_read, "%d", &cmd);
        printf("cmd = %d\n", cmd);
        if (cmd == CMD_PUSH)
        {
            fscanf(mach_code_read, "%d", &arg1);
            printf("arg1 = %d\n", arg1);
            StackPush(&stk, arg1);
        }

        else if (cmd == CMD_ADD)
        {
            StackPush(&stk, StackPop(&stk) + StackPop(&stk));
        }

        else if (cmd == CMD_SUB)
        {
            int el_sub1 = StackPop(&stk);
            int el_sub2 = StackPop(&stk);
            StackPush(&stk, el_sub2 - el_sub1);
        }

        else if (cmd == CMD_MUL)
        {
            StackPush(&stk, StackPop(&stk) * StackPop(&stk));
        }

        else if (cmd == CMD_DIV)
        {
            int el_div1 = StackPop(&stk);
            int el_div2 = StackPop(&stk);
            StackPush(&stk, el_div2 / el_div1);
        }

        /*if (cmd == CMD_SQRT)
        {
            StackPush(&stk, sqrt(StackPop(&stk)));
        }*/

        else if (cmd == CMD_DUMP)
        {
            StackDump(&stk, __func__, __FILE__, __LINE__, RUN);
        }

        else if (cmd == CMD_OUT)
        {
            printf("%d", StackPop(&stk));
        }

        else if (cmd == CMD_HLT)
        {
            break;
        }

        else
        {
            printf("\n<<<<<<SYNTAX ERROR>>>>>>: %d\n\n", cmd);
        }
    }

    fclose(mach_code_read);
    return 0;
}

int CountCommands()
{
    FILE *mach_code_read = fopen(MACHINE_CODE, "rb");

    fseek(mach_code_read, 0, SEEK_END);
    int file_size = ftell(mach_code_read);
    fclose(mach_code_read);
    return file_size;
}
/*void InitCode()
{
    FILE *mach_code = fopen(MACHINE_CODE, "r");

    fread(code, );
}*/
