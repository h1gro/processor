#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>

#include "assembler.h"

int main()
{
    struct assembler assm                = {};
    struct stat st_file                  = {};
    struct label labels[NUMBER_OF_MARKS] = {};

    InitStat(&st_file);

    StructAssmCtor(&assm, &st_file); //TODO отдельный буффер для кода

    LabelsCtor(&assm); //TODO use Onegin + skip_spaces()

    CompileCommands(&assm); //TODO двухпроходная компиляция не работает

    StructAssmDtor(&assm);

    LabelsDtor(&assm);

    return 0;
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

