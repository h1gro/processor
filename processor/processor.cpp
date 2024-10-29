#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../stack/global.h"
#include "processor.h"
#include "ReadByteFile.h"
#include "C_Dtors.h"
#include "LaunchCommand.h"

int main()
{
    struct spu_t spu     = {};
    struct stat commands = {};

    InitStat(&commands);
    SpuCtor(&spu, &commands);

    ReadByteFile(&spu);

    LaunchCommand(&spu);

    StackDtor(&spu.stk);
    SpuDtor(&spu);
    return 0;
}


