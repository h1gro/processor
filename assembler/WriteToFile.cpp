#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "assembler.h"
#include "WriteToFile.h"
#include "label_table.h"

void CompileCommands(struct assm* global_assm, struct stat* st_file) //TODO read strcpy()
{
    assert(global_assm);
    assert(global_assm->commands_file);
    assert(global_assm->byte_code_write);
    assert(global_assm->command);
    assert(global_assm->labels);

    int arg = 0, number_command = 0;
    char jmp_arg[SIZE_LABEL] = {};

    while (fscanf(global_assm->commands_file, "%s", global_assm->command) != EOF) //TODO use onegin // make dir lib and stack in this
    {
        printf("command = %s\n", global_assm->command); //TODO Деффайны - это не круто!!!!

        COMPILATION_ARG("push", PUSH);

        COMPILATION_REGS("pushr", PUSHR);

        COMPILATION_JMP("jmp", JUMP);

        COMPILATION_JMP("jb", JB);

        COMPILATION_JMP("jbe", JBE);

        COMPILATION("sub", SUB);

        COMPILATION("div", DIV);

        COMPILATION("add", ADD);

        COMPILATION("mul", MUL);

        COMPILATION("dump", DUMP); //TODO not printf after scanf use buffer

        COMPILATION("hlt", HLT);

        DefineArg(global_assm, number_command);
    }
}

void DefineArg(struct assm* global_assm, int number_command) //TODO rename this fucking func (shit)
{
    if (strchr((const char*)global_assm->command, ':') != NULL)
    {
        printf("\ni am in compilation (define_arg)\n");

        global_assm->labels[global_assm->ip_label].addr = number_command;
        global_assm->labels[global_assm->ip_label].mark = global_assm->command;

        printf("ip_mark = %d, addr = %d, mark = %s\n",
                global_assm->ip_label, global_assm->labels[global_assm->ip_label].addr,
                global_assm->labels[global_assm->ip_label].mark);

        number_command++;
        global_assm->ip_label++;
    }
}

int DefineReg(struct assm* global_assm)
{
    assert(global_assm);
    assert(global_assm->commands_file);
    assert(global_assm->byte_code_write);
    assert(global_assm->command);

    char reg[SIZE_REG] = {};

    assert(reg);

    fscanf(global_assm->commands_file, "%s", reg);

    REGS("ax", AX);

    REGS("bx", BX);

    REGS("cx", CX);

    REGS("dx", DX);

    printf("\n<<<<<<WRONG REGISTER IN COMMANDS FILE!>>>>>>\n\n");
    return - 153;

}
