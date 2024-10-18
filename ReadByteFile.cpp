#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>

#include "global.h"
#include "processor.h"
#include "ReadByteFile.h"
#include "C_Dtor.h"

void InitStat(struct stat* commands) //TODO SPLIT INTO PROGRAMS
{
    stat(BYTE_CODE_R, commands);

    assert(commands->st_size);

    printf("st_size = %ld\n", commands->st_size);
}

void ReadByteFile(struct spu_t* spu, struct stat* commands)
{
    FILE *byte_code_read = fopen(BYTE_CODE_R, "rb");

    assert(byte_code_read);

    SpuCtor(spu, commands);

    FillingCode(spu, byte_code_read); //TODO Onegin func

    fclose(byte_code_read);
}

void FillingCode(struct spu_t* spu, FILE* byte_code_read)
{
    while(!feof(byte_code_read))
    {
        fscanf(byte_code_read, "%d", &spu->code[spu->ip]); //TODO use-library func
        printf("%d\n", spu->code[spu->ip]);
        spu->ip++;
    }
}

void LaunchCommand(struct stat* commands, struct spu_t* spu)
{
    for(spu->ip = 0; spu->ip < commands->st_size; spu->ip++)
    {
        int arg1 = 0, el_sub1 = 0, el_sub2 = 0, el_div1 = 0, el_div2 = 0, el_jb1 = 0, el_jb2 = 0;

        //printf("code[i] = %d\n", spu->code[spu->ip]);
        //printf("cmd = %d\n", cmd);
        assert(spu->ip >= 0);

        printf("%d %d\n", spu->code[spu->ip], spu->ip);

        switch(spu->code[spu->ip])
        {
        case CMD_PUSH: arg1 = spu->code[spu->ip + NUM_ARGS_PUSH];
                       //printf("arg1 = %d\n", arg1);
                       StackPush(&spu->stk, arg1);

                       spu->ip++;
                       break;

        case CMD_ADD:  StackPush(&spu->stk, StackPop(&spu->stk) + StackPop(&spu->stk));
                       break;

        case CMD_SUB:  el_sub1 = StackPop(&spu->stk);
                       el_sub2 = StackPop(&spu->stk);

                       StackPush(&spu->stk, el_sub2 - el_sub1);
                       break;

        case CMD_MUL:  StackPush(&spu->stk, StackPop(&spu->stk) * StackPop(&spu->stk));
                       break;

        case CMD_DIV:  el_div1 = StackPop(&spu->stk);
                       el_div2 = StackPop(&spu->stk);

                       assert(el_div1);

                       StackPush(&spu->stk, el_div2 / el_div1);
                       break;

        case CMD_DUMP: StackDump(&spu->stk, __func__, __FILE__, __LINE__, RUN);
                       break;

        case CMD_OUT:  printf("%d", StackPop(&spu->stk));
                       break;

        case CMD_JUMP: spu->ip = spu->code[spu->ip + NUM_ARGS_JMP] - 1; //TODO const
                       printf("ip after jmp = %d\n", spu->ip);
                       break;

        case CMD_JB:   el_jb1 = StackPop(&spu->stk);
                       el_jb2 = StackPop(&spu->stk);
                       if(el_jb2 > el_jb1)
                       {
                           spu->ip = spu->code[spu->ip + NUM_ARGS_JMP];
                       }
                       break;

        case CMD_JBE:  el_jb1 = StackPop(&spu->stk);
                       el_jb2 = StackPop(&spu->stk);
                       if(el_jb2 >= el_jb1)
                       {
                           spu->ip = spu->code[spu->ip + NUM_ARGS_JMP];
                       }
                       break;

        case CMD_HLT:  break;

        default:       printf("\n<<<<<<SYNTAX ERROR>>>>>>: %d\n\n", spu->code[spu->ip]);
        }
    }
}
