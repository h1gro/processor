#include <stdio.h>

#include "../stack/global.h"
#include "processor.h"
#include "SpuC_Dtor.h"
#include "C_Dtors.h"
#include "ReadByteFile.h"

void Ctors(struct spu_t* spu, struct stat* commands) //TODO объединить с spu ctor  в один файл
{
    InitStat(commands);
    StackCtor(&spu->stk); //TODO перенести в spu
    SpuCtor(spu, commands);
}

void Dtors(struct spu_t* spu)
{
    StackDtor(&spu->stk);
    SpuDtor(spu);
}
