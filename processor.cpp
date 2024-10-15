#include <stdio.h>
#include <sys\stat.h>
#include <math.h>
#include <assert.h>

#include "global.h"
#include "processor.h"

int CountCommands();

int main()
{
    struct stat commands = {};
    stat(MACHINE_CODE, &commands);
    printf("st_size = %d\n", commands.st_size);

    FILE *mach_code_read = fopen(MACHINE_CODE, "rb");

    int* code = (int*) calloc(commands.st_size, sizeof(int));
    printf("code: %s\n", code);

    printf("YAU TUT\n");
    assert(mach_code_read);

    int i = 0;
    while(!feof(mach_code_read))
    {
        printf("YAU TUT1\n");
        fscanf(mach_code_read, "%d", &code[i]);
        printf("%d\n", code[i]);
        i++;
    }
    printf("code: %s\n", code);

    struct stack_t stk = {INIT(CANARY, stk)};

    StackCtor(&stk);

    for(i = 0; i < commands.st_size; i++)
    {
        int arg1 = 0;
        int cmd = code[i];

        printf("code[i] = %d\n", code[i]);
        printf("cmd = %d\n", cmd);

        if (cmd == CMD_PUSH)
        {
            arg1 = code[i+1];
            printf("arg1 = %d\n", arg1);
            StackPush(&stk, arg1);
            i++;
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
