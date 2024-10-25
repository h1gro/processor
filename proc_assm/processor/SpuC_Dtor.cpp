#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#include "../stack/global.h"
#include "processor.h"
#include "SpuC_Dtor.h"

void SpuCtor(struct spu_t* spu, struct stat* commands)
{
    assert(spu);
    assert(commands);
    assert(commands->st_size);

    spu->code      = (int*) calloc((size_t)(commands->st_size), sizeof(int));
    spu->registers = (int*) calloc(NUM_REGISTERS, sizeof(int));

    assert(spu->code);
    assert(spu->registers);



    spu->ip = 0;
}

void SpuDtor(struct spu_t* spu)
{
    assert(spu);

    spu->ip = 0;

    free(spu->code);
    free(spu->registers);
}
