#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../lib/stack/global.h"
#include "processor.h"

int main()
{
    struct spu_t spu     = {};
    struct stat commands = {};

    InitStat(&commands);
    SpuCtor(&spu, &commands);

    ReadByteFile(&spu);

    LaunchCommand(&spu);

    SpuDtor(&spu);
    return 0;
}


