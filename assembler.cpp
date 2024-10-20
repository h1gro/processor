#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "assembler.h"

int main()
{
    struct file_t file = {};

    StrFilesCtor(&file);

    WriteToFile(&file);

    StrFilesDtor(&file);

    return 0;
}

void WriteToFile(struct file_t* file) //TODO read strcpy()
{
    int arg = 0;
    while (fscanf(file->commands_file, "%s", file->command) != EOF) //TODO use onegin // make dir lib and stack in this
    {
        assert(file->command);

        COMPILATION_ARG("push", PUSH);

        COMPILATION_ARG("jmp", JUMP);

        COMPILATION_ARG("jb", JB);

        COMPILATION_ARG("jbe", JBE);

        COMPILATION("sub", SUB);

        COMPILATION("div", DIV);

        COMPILATION("add", ADD);

        COMPILATION("mul", MUL);

        COMPILATION("dump", DUMP); //TODO not printf after scanf use buffer

        COMPILATION("hlt", HLT);
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
