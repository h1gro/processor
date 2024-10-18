#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>

#include "global.h"
#include "processor.h"
#include "C_Dtor.h"

void SpuCtor(struct spu_t* spu, struct stat* commands)
{
    spu->code      = (int*) calloc(commands->st_size, sizeof(int));
    spu->registers = (int*) calloc(NUM_REGISTERS, sizeof(int));

    assert(spu->code);
    assert(spu->registers);

    spu->ip = 0;
}

void SpuDtor(struct spu_t* spu)
{
    spu->ip = 0;

    free(spu->code);
    free(spu->registers);
}
