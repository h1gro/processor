#include <stdio.h>
#include <stdlib.h>
#include <sys\stat.h>

#include "global.h"
#include "processor.h"
#include "ReadByteFile.h"
#include "C_Dtor.h"

int main()
{
    struct spu_t spu     = {};
    struct stat commands = {};

    InitStat(&commands);
    StackCtor(&spu.stk);

    ReadByteFile(&spu, &commands);

    LaunchCommand(&commands, &spu);

    SpuDtor(&spu);
    return 0;
}


