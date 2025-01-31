#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "assembler.h"
#include "../Commands.h"

void CompileCommands(struct assembler* assm)
{
    assert(assm);
    assert(assm->commands_file);
    assert(assm->byte_code_write);
    assert(assm->labels);

    char jmp_arg[SIZE_LABEL] = {};

    assert(jmp_arg);

    for (assm->index = 0; assm->index < assm->capacity; assm->index++)
    {
        WriteCommand(assm);

        assm->cmd_size = 0;

        COMPILATION(PUSH);

        COMPILATION(POP);

        COMPILATION(JUMP);

        COMPILATION(JB);

        COMPILATION(JBE);

        COMPILATION(JA);

        COMPILATION(JAE);

        COMPILATION(SUB);

        COMPILATION(DIV);

        COMPILATION(ADD);

        COMPILATION(MUL);

        COMPILATION(DUMP);

        COMPILATION(SQRT);

        COMPILATION(SSQRT);

        COMPILATION(CIRCLE);

        COMPILATION(HLT);

        // if (strcasecmp((const char*)assm->command, "factorial") == 0)
        // {
        //     FactorialCode(assm);
        // }

        for (int j = 0; j < 5; j++)
        {
            printf("%c", assm->command[j]);
        }

        printf("\n");

        assert(assm);

        LabelAssignment(assm); //TODO вынести из command

        free(assm->command);
    }
}

int DefineReg(struct assembler* assm)
{
    assert(assm);
    assert(assm->commands_file);
    assert(assm->byte_code_write);

    int wrcmd = WriteCommand(assm);

    if (wrcmd == OPER_ARG)
    {
        return OPER_ARG;
    }

    else if (wrcmd == MEMORY_PUSH)
    {
        return MEMORY_PUSH;
    }

    int check_regs_return = CheckRegs(assm);

    if (check_regs_return == NO_REGS)
    {
        return INT_ARG;
    }

    else
    {
        return check_regs_return;
    }
}

void CheckArg(struct assembler* assm)
{
    assert(assm);
    assert(assm->commands_file);
    assert(assm->byte_code_write);

    if (assm->last_command == PUSH)
    {
        UniversalPush(assm);
    }

    else if (assm->last_command == POP)
    {
        SkipSpaces(assm, assm->input_code[assm->index], ' ');

        fprintf(assm->byte_code_write, "%d", DefineReg(assm));

        free(assm->command);
    }

    else if ((assm->last_command == JUMP) || (assm->last_command == JBE) || (assm->last_command == JB) || (assm->last_command == JA) || (assm->last_command == JAE))
    {
        assm->index++;

        WriteCommand(assm);

        FindLabel(assm);

        free(assm->command);

        printf("<<<<<<<<<<<<<<<<<<<3\n");

        assm->num_elem_file++;
    }

    fprintf(assm->byte_code_write, "\n");
}

void UniversalPush(struct assembler* assm)
{
    assert(assm);
    assert(assm->byte_code_write);
    assert(assm->command);

    SkipSpaces(assm, assm->input_code[assm->index], ' ');

    if (assm->input_code[assm->index] == '[')
    {
        fprintf(assm->byte_code_write, "%d ", CMD_MEMORY_PUSH);

        assm->index++;

        // UniversalPush(assm);
        WriteCommand(assm);

        for (int i = 0; i < assm->cmd_size; i++)
        {
            fprintf(assm->byte_code_write, "%c", assm->command[i]);
        }

        free(assm->command);
    }

    else
    {
        int reg_return = DefineReg(assm);

        //printf("\n\nreg_return = %d\n", reg_return);

        if (reg_return == INT_ARG)
        {
            fprintf(assm->byte_code_write, "%d ", CMD_STACK_PUSH);

            for (int i = 0; i < assm->cmd_size; i++)
            {
                fprintf(assm->byte_code_write, "%c", assm->command[i]);
            }

            assm->num_elem_file += 2;
        }

        else if (reg_return == OPER_ARG)
        {
            int check_regs_return = CheckRegs(assm);

            fprintf(assm->byte_code_write, "%d %d ", CMD_REG_TO_STACK, check_regs_return);

            switch (assm->input_code[assm->index])
            {
                case '+':
                {
                    fprintf(assm->byte_code_write, "%d ", ADD);
                    break;
                }

                case '-':
                {
                    fprintf(assm->byte_code_write, "%d ", SUB);
                    break;
                }

                case '*':
                {
                    fprintf(assm->byte_code_write, "%d ", MUL);
                    break;
                }

                case '/':
                {
                    fprintf(assm->byte_code_write, "%d ", DIV);
                    break;
                }
            }

            free(assm->command);

            assm->index++;
            assm->num_elem_file += 4;

            WriteCommand(assm);

            printf("\n\n");
            for (int i = 0; i < assm->cmd_size; i++)
            {
                printf("%c", assm->command[i]);
                fprintf(assm->byte_code_write, "%c", assm->command[i]);
            }
            printf("\n\n");
        }

//         else if (reg_return == MEMORY_PUSH)
//         {
//
//         }

        else
        {
            // printf("\n\nDefineReg return = %d\n\n", reg_return);
            fprintf(assm->byte_code_write, "%d %d", CMD_REG_PUSH, reg_return);

            assm->num_elem_file += 2;
        }

        free(assm->command);

    }
}

void SkipSpaces(struct assembler* assm, int symbol0, int symbol1)
{
        assert(assm);

        printf("SKIPSPACES\n\n%c - %d\n%c - %d \n", symbol0, symbol0, symbol1, symbol1);

        while (symbol0 == symbol1)
        {
            assm->index++;

            symbol0 = assm->input_code[assm->index];

            printf("%c - %d\n", symbol0, symbol0);
            //printf("buffer[%lu] = %c\n", akin->index_buf, symbol0);
        }
}

int WriteCommand(struct assembler* assm)
{
    assm->command = (char*) calloc(COMMAND_SIZE, sizeof(char));

    assert(assm->command);

    assm->cmd_size = 0;
    int symbols = 0;
    printf("\nI AM WRITING A COMMAND!\n\n");

    while ((assm->input_code[assm->index] != '\n') && (assm->input_code[assm->index] != '\0') && (assm->input_code[assm->index] != ' ') && (assm->input_code[assm->index] != '\r') && (assm->input_code[assm->index] != ':'))
    {
        if (((assm->input_code[assm->index] == '+') || (assm->input_code[assm->index] == '-') || (assm->input_code[assm->index] == '*') || (assm->input_code[assm->index] == '/')) && (symbols != 0))
        {
            return OPER_ARG;
        }

        if ( (assm->input_code[assm->index] == ']'))
        {
            return MEMORY_PUSH;
        }

        assm->command[assm->cmd_size] = assm->input_code[assm->index];

        printf("%c - %d\n", assm->command[assm->cmd_size], assm->command[assm->cmd_size]);

        assm->cmd_size++;
        assm->index++;
        symbols++;
    }

    return NOT_OPER_ARG;
}

int CheckRegs(struct assembler* assm)
{
    assert(assm);

    REGS(AX);

    REGS(BX);

    REGS(CX);

    REGS(DX);

    return NO_REGS;
}

// void FactorialCode(struct assembler* assm)
// {
//     assert(assm);
//     fprintf(assm->byte_code_write, "push ");
//
//     WriteCommand(assm);
//
//     for (int i = 0; i < assm->cmd_size; i++)
//     {
//         fprintf(assm->byte_code_write, "%d", assm->command[i]);
//     }
//
//     fprintf(assm->byte_code_write, "\n1 1 -2\n1 0 1\n1 1 -3\n1 0 1\n"
//                                    "1 1 -4\n1 2 -3 4 0\n
// 1 2 -4 4 0
// 5
// 18 -4
// 1 1 -4
// 1 0 1
// 1 1 -3
// 1 0 1
// 1 1 -1
// 1 2 -1 4 0
// 1 2 -2 4 0
// 15 18");
//     free(assm->command);
// }
