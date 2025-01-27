#include <stdio.h>
#include <assert.h>

#include "../lib/stack/global.h"
#include "processor.h"
#include "../Commands.h"

void LaunchCommand(struct spu_t* spu)
{
    assert(spu->code);
    assert(spu->registers);
    assert(spu->code_elems);

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
            case PUSH:
            {
                arg1 = spu->code[spu->ip + COMMAND_ARGS]; //TODO сделать общий enum
                //printf("arg1 = %d\n", arg1);
                StackPush(&spu->stk, arg1);

                spu->ip++;
                break;
            }

            case PUSHR:
            {
                arg1 = spu->code[spu->ip + COMMAND_ARGS];
                printf("register = %d\n", arg1);
                PushRegister(spu->registers, arg1);

                spu->ip++;
                break;
            }

            case ADD:
            {
                StackPush(&spu->stk, StackPop(&spu->stk) + StackPop(&spu->stk));
                break;
            }

            case SUB:
            {
                arg1 = StackPop(&spu->stk);
                arg2 = StackPop(&spu->stk);

                StackPush(&spu->stk, arg2 - arg1);
                break;
            }

            case MUL:
            {
                arg1 = StackPop(&spu->stk);
                arg2 = StackPop(&spu->stk);

                StackPush(&spu->stk, arg1 * arg2);
                break;
            }

            case DIV:
            {
                arg1 = StackPop(&spu->stk);
                arg2 = StackPop(&spu->stk);

                if (arg1 == 0)
                {
                    printf("\n<<<<<<DIVISION BY ZERO!>>>>>>\n\n");
                    break;
                }

                StackPush(&spu->stk, arg2 / arg1);
                break;
            }

            case DUMP:
            {
                StackDump(&spu->stk, __func__, __FILE__, __LINE__, RUN);
                break;
            }

            case OUT:
            {
                printf("%d", StackPop(&spu->stk));
                break;
            }

            case JUMP:
            {
                if (spu) spu->ip = spu->code[spu->ip + COMMAND_ARGS] - COMMAND_SHIFT;

                printf("ip after jmp = %d\n", spu->ip);
                break;
            }

            case JB:   JUMP(>);

            case JBE:  JUMP(>=);

            case JA:   JUMP(<);

            case JAE:  JUMP(<=);

            case HLT:  break;

            default: printf("\n<<<<<<SYNTAX ERROR>>>>>>: %d\n\n", spu->code[spu->ip]);
        }
    }

    printf("ax = %d, bx = %d, cx = %d, dx = %d\n", spu->registers[0], spu->registers[1], spu->registers[2], spu->registers[3]);

    return;
}

void PushRegister(int* data, int reg)
{
    assert(data);

    printf("\nreg = %d\n", reg);

    switch(reg)
    {
        case AX:    REGS(AX);

        case BX:    REGS(BX);

        case CX:    REGS(CX);

        case DX:    REGS(DX);

        default:    printf("\n<<<<<<WRONG REGISTER!>>>>>>\n\n");
    }

    printf("here\n");
}
