#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>

#include "assembler.h"

int main()
{
    struct assembler assm                 = {};
    struct stat st_file                   = {};
    struct label labels[NUMBER_OF_LABELS] = {};

    InitStat(&st_file);

    StructAssmCtor(&assm, &st_file);

    LabelsCtor(&assm);

    CompileCommands(&assm); //TODO двухпроходная компиляция не работает

    fseek(assm.byte_code_write, 0L, SEEK_SET);

    CompileCommands(&assm);

    StructAssmDtor(&assm);

    LabelsDtor(&assm);

    return 0;
}

//TODO
//4) label :1 not use label into stack
//5) registers - use bytecode
//6.5) memory regs push [rax]
//7) Sdl and sfml

