#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "assembler.h"
#include "CompileCommands.h"
#include "label_table.h"

void CompileCommands(struct assembler* assm) //TODO read strcpy()
{
    assert(assm);
    assert(assm->commands_file);
    assert(assm->byte_code_write);
    assert(assm->labels);

    char jmp_arg[SIZE_LABEL] = {};

    assert(jmp_arg);

    int n = 1, checker = 0;

    for (assm->index = 0; assm->index < assm->capacity; assm->index++)
    {
        checker = 0;

        WriteCommand(assm);

        COMPILATION("push", PUSH); //TODO # создает строку из названия переменной (сделать вместо двух аргументов один)

        COMPILATION("pushr", PUSHR); //TODO universial push

        COMPILATION("jmp", JUMP); //TODO more jumps

        COMPILATION("jb", JB);

        COMPILATION("jbe", JBE);

        COMPILATION("sub", SUB);

        COMPILATION("div", DIV);

        COMPILATION("add", ADD);

        COMPILATION("mul", MUL);

        COMPILATION("dump", DUMP); //TODO not printf after scanf use buffer

        COMPILATION("hlt", HLT);

        if (checker == 0)
        {
            for (int j = 0; j < 5; j++)
            {
                printf("%c", assm->command[j]);
            }

            printf("\n");

            assert(assm);

            LabelAssignment(assm); //TODO вынести из command
        }

        free(assm->command);
    }
}

int DefineReg(struct assembler* assm)
{
    assert(assm);
    assert(assm->commands_file);
    assert(assm->byte_code_write);
    assert(assm->command);

    REGS("ax", AX);

    REGS("bx", BX);

    REGS("cx", CX);

    REGS("dx", DX);

    return INT_ARG;
}

void CheckArg(struct assembler* assm)
{
    assert(assm);
    assert(assm->commands_file);
    assert(assm->byte_code_write);

    if (assm->last_command == PUSH)
    {
        while ((assm->input_code[assm->index] != '\n') && (assm->input_code[assm->index] != '\r'))
        {
            SkipSpaces(assm, assm->input_code[assm->index], ' '); //аски код пробела

            fprintf(assm->byte_code_write, "%c", assm->input_code[assm->index]);

            assm->index++;

            //UniversalPush(assm);
        }
    }

    else if ((assm->last_command == JUMP) || (assm->last_command == JBE) || (assm->last_command == JB))
    {
        free(assm->command);

        assm->index++;

        WriteCommand(assm);

        FindLabel(assm);

        printf("<<<<<<<<<<<<<<<<<<<3\n");
    }

    fprintf(assm->byte_code_write, "\n");
}

void UniversalPush(struct assembler* assm)
{
    assert(assm);
    assert(assm->byte_code_write);
    assert(assm->command);

    if (DefineReg(assm) == INT_ARG)
    {
        fprintf(assm->byte_code_write, "%s", assm->command);
    }

    else
    {
        fprintf(assm->byte_code_write, "%d", DefineReg(assm));
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

void WriteCommand(struct assembler* assm)
{
    int i = 0;

    assm->command = (char*) calloc(COMMAND_SIZE, sizeof(char));

    assert(assm->command);

    printf("\nI AM WRITING A COMMAND!\n\n");
    while ((assm->input_code[assm->index] != '\n') && (assm->input_code[assm->index] != '\0') && (assm->input_code[assm->index] != ' ') && (assm->input_code[assm->index] != '\r')  && (assm->input_code[assm->index] != ':'))
    {
        assm->command[i] = assm->input_code[assm->index];

        printf("%c - %d\n", assm->command[i], assm->command[i]);

        i++;
        assm->index++;
    }
}
