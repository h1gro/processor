#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "global.h"
#include "processor.h"
#include "ReadByteFile.h"
#include "SpuC_Dtor.h"
#include "C_Dtors.h"

int main()
{
    struct spu_t spu     = {};
    struct stat commands = {};

    Ctors(&spu, &commands);

    ReadByteFile(&spu);

    LaunchCommand(&spu);

    Dtors(&spu);
    return 0;
}


