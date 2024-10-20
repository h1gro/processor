#include <stdio.h>

#include "global.h"
#include "processor.h"
#include "SpuC_Dtor.h"
#include "C_Dtors.h"
#include "ReadByteFile.h"

void Ctors(struct spu_t* spu, struct stat* commands)
{
    InitStat(commands);
    StackCtor(&spu->stk);
    SpuCtor(spu, commands);
}

void Dtors(struct spu_t* spu)
{
    StackDtor(&spu->stk);
    SpuDtor(spu);
}
