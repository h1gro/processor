#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "assembler.h"
#include "label_table.h"

int main()
{
    struct file_t file = {};
    struct stat st_file = {};
    struct label labels[NUMBER_OF_MARKS] = {};

    InitStat(&st_file);
    StrFilesCtor(&file, &st_file);
    LabelsCtor(labels);

    WriteToFile(&file, &st_file, labels);

    StrFilesDtor(&file);
    LabelsDtor(labels);

    return 0;
}

void WriteToFile(struct file_t* file, struct stat* st_file, struct label* labels) //TODO read strcpy()
{
    assert(file);

    int arg = 0, number_command = 0, addr = - 513, ip_mark = 0;
    char str_arg[10] = {};
    while (fscanf(file->commands_file, "%s", file->command) != EOF) //TODO use onegin // make dir lib and stack in this
    {
        assert(file->command);

        printf("command = %s\n", file->command);

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

        printf("iteration\n");
    }

    //free(buffer);
}

int WhatIsReg(struct file_t* file)
{
    assert(file);

    char* reg =(char*) calloc(SIZE_REG, sizeof(char));

    assert(reg);

    fscanf(file->commands_file, "%s", reg);

    if (strcmp((const char*)reg, "ax") == 0){free(reg); return AX;}

    if (strcmp((const char*)reg, "bx") == 0){free(reg); return BX;}

    if (strcmp((const char*)reg, "cx") == 0){free(reg); return CX;}

    if (strcmp((const char*)reg, "dx") == 0){free(reg); return DX;}

    else
    {
        printf("\n<<<<<<WRONG REGISTER IN COMMANDS FILE!>>>>>>\n\n");
        free(reg);
        return - 153;
    }
}

//TODO
//0) Theory
//1) vsl or linux
//2) разбей всё на папки
//3) todo
//4) label :1 not use label into stack
//5) registers - use bytecode
//6) memory push [1] and 6.5) memory regs push [rax]
//7) Sdl and sfml

// void CreateBuf(struct file_t* file, struct stat* st_file)
// {
//     char* buffer = (char*) calloc((size_t)(st_file->st_size), sizeof(char));
//
//     assert(buffer);
//
//     fgets(file->command, (int)(st_file->st_size), file->commands_file);
//
//     printf("commands: %s", file->command);
//
//     assert(file->command);
//
//     strcpy(buffer, (const char*)file->command);
// }
