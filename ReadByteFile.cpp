#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#include "global.h"
#include "processor.h"
#include "ReadByteFile.h"
#include "SpuC_Dtor.h"

const char* BYTE_CODE_R = "byte_code.txt";

void InitStat(struct stat* commands) //TODO SPLIT INTO PROGRAMMS
{
    stat(BYTE_CODE_R, commands);

    assert(commands->st_size);

    printf("st_size = %ld\n", commands->st_size);
}

void ReadByteFile(struct spu_t* spu)
{
    FILE *byte_code_read = fopen(BYTE_CODE_R, "rb");

    assert(byte_code_read);

    FillingCode(spu, byte_code_read); //TODO Onegin func

    fclose(byte_code_read);
}

void FillingCode(struct spu_t* spu, FILE* byte_code_read)
{
    while(!feof(byte_code_read))
    {
        fscanf(byte_code_read, "%d", &spu->code[spu->ip]); //TODO use-library func
        printf("%d\n", spu->code[spu->ip]);

        spu->code_elems++;
        spu->ip++; //TODO const size of command
    }
}

void LaunchCommand(struct spu_t* spu)
{
    assert(spu->code);
    assert(spu->registers);

    for(spu->ip = 0; spu->ip < spu->code_elems; spu->ip++)
    {
        int arg1 = 0, arg2 = 0;

        printf("code[i] = %d\n", spu->code[spu->ip]);
        printf("code_elems = %d\n", spu->code_elems);
        printf("ip = %d\n", spu->ip);

        assert(spu->ip >= 0);

        printf("%d %d\n", spu->code[spu->ip], spu->ip);

        switch(spu->code[spu->ip])
        {
        case CMD_PUSH: arg1 = spu->code[spu->ip + COMMAND_ARGS];
                       //printf("arg1 = %d\n", arg1);
                       StackPush(&spu->stk, arg1);

                       spu->ip++;
                       break;

        case CMD_ADD:  StackPush(&spu->stk, StackPop(&spu->stk) + StackPop(&spu->stk)); //TODO  проверку в стеке через if а не assert(), лучше добавить проверку и в проц.
                       break;

        case CMD_SUB:  arg1 = StackPop(&spu->stk);
                       arg2 = StackPop(&spu->stk);

                       StackPush(&spu->stk, arg2 - arg1);
                       break;

        case CMD_MUL:  arg1 = StackPop(&spu->stk);
                       arg2 = StackPop(&spu->stk);

                       StackPush(&spu->stk, arg1 * arg2);
                       break;

        case CMD_DIV:  arg1 = StackPop(&spu->stk);
                       arg2 = StackPop(&spu->stk);

                       if (arg1 == 0)
                       {
                           printf("\n<<<<<<DIVISION BY ZERO!>>>>>>\n\n");
                           break;
                       }

                       StackPush(&spu->stk, arg2 / arg1);
                       break;

        case CMD_DUMP: StackDump(&spu->stk, __func__, __FILE__, __LINE__, RUN);
                       break;

        case CMD_OUT:  printf("%d", StackPop(&spu->stk));
                       break;

        case CMD_JUMP: spu->ip = spu->code[spu->ip + COMMAND_ARGS] - COMMAND_SHIFT;
                       printf("ip after jmp = %d\n", spu->ip);
                       break;

        case CMD_JB:   IP_SHIFT(>);

        case CMD_JBE:  IP_SHIFT(>=);

        case CMD_HLT:  break;

        default:       printf("\n<<<<<<SYNTAX ERROR>>>>>>: %d\n\n", spu->code[spu->ip]);
        }
    }

    return;
}
