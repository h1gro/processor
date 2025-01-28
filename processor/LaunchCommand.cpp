#include <stdio.h>
#include <assert.h>

#include "../lib/stack/global.h"
#include "processor.h"
#include "TasksFunctions.h"

void LaunchCommand(struct spu_t* spu)
{
    assert(spu->code);
    assert(spu->registers);
    assert(spu->code_elems);

    int id_file_open = 0;

    FILE* equation = NULL;

    for(spu->ip = 0; spu->ip < spu->code_elems; spu->ip++)
    {
        double arg1 = 0, arg2 = 0;

        printf("code[i] = %d\n", spu->code[spu->ip]);
        printf("code_elems = %d\n", spu->code_elems);
        printf("ip = %d\n", spu->ip);

        assert(spu->ip >= 0);

        printf("\n%d %d\n", spu->code[spu->ip], spu->ip);

        switch(spu->code[spu->ip])
        {
            case PUSH:
            {
                UniversalPush(spu);
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
                printf("%lg", StackPop(&spu->stk));
                break;
            }

            case SSQRT:
            {
                if (!id_file_open)
                {
                    equation = fopen(SQUARE_EQUATION, "w+");
                    assert(equation);

                    id_file_open = 1;
                }

                SolveSquare(spu, equation);
                break;
            }

            case JUMP:
            {
                if (spu) spu->ip = spu->code[spu->ip + CMD_SHIFT] - CMD_SHIFT;

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

    if (equation)
    {
        fclose(equation);
    }

    printf("ax = %lg, bx = %lg, cx = %lg, dx = %lg\n", spu->registers[0], spu->registers[1], spu->registers[2], spu->registers[3]);

    return;
}

void UniversalPush(struct spu_t* spu)
{
    int arg1 = 0;

    spu->ip++;

    int push_code = spu->code[spu->ip];

    if (push_code == CMD_STACK_PUSH)
    {
        spu->ip++;

        arg1 = spu->code[spu->ip];

        printf("arg1 = %d\n", arg1);

        StackPush(&spu->stk, arg1);
    }

    else if (push_code == CMD_REG_PUSH)
    {
        spu->ip++;

        int reg = spu->code[spu->ip];

        printf("register = %d\n", reg);

        PushRegister(spu, spu->registers, reg);
    }

    else if (push_code == CMD_REG_TO_STACK)
    {
        int ip_register = 0;

        spu->ip++;

        printf("\nMY HAHAH = %d\n\n", spu->code[spu->ip]);

        switch(spu->code[spu->ip])
        {
            case AX:
            {
                WHAT_IS_REG(AX);
                break;
            }

            case BX:
            {
                WHAT_IS_REG(BX);
                break;
            }

            case CX:
            {
                WHAT_IS_REG(CX);
                break;
            }

            case DX:
            {
                WHAT_IS_REG(DX);
                break;
            }

            default:    printf("\n<<<<<<WRONG REGISTER!>>>>>>\n\n");
        }

        printf("\nIP_REGISTER1 = %d, what[reg] = %lg\n\n", ip_register, spu->registers[ip_register]);
        spu->ip++;

        switch(spu->code[spu->ip])
        {
            case ADD:
            {
                WHAT_IS_OPER(+);
                break;
            }

            case SUB:
            {
                WHAT_IS_OPER(-);
                break;
            }

            case MUL:
            {
                WHAT_IS_OPER(*);
                break;
            }

            case DIV:
            {
                WHAT_IS_OPER(/);
                break;
            }

            default:    printf("\n<<<<<<WRONG OPERATOR!>>>>>>\n\n");
        }
    }

    else
    {
        printf("\nUnknow command for push!\n\n");
    }
}

regs PushRegister(struct spu_t* spu, double* data, int reg)
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
}
