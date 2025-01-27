#include <stdio.h>
#include <sys/stat.h>

#include "../lib/stack/global.h"
#include "processor.h"

void SpuCtor(struct spu_t* spu, struct stat* commands)
{
    assert(spu);
    assert(commands);
    assert(commands->st_size);

    spu->code      = (int*) calloc((size_t)(commands->st_size), sizeof(int));
    spu->registers = (int*) calloc(NUM_REGISTERS, sizeof(int));

    assert(spu->code);
    assert(spu->registers);

    StackCtor(&spu->stk);

    spu->ip = 0;
}

void SpuDtor(struct spu_t* spu)
{
    assert(spu);

    spu->ip = 0;

    free(spu->code);
    free(spu->registers);
}

void InitStat(struct stat* commands)
{
    assert(commands);

    stat(BYTE_CODE_R, commands);

    assert(commands->st_size);

    printf("st_size = %ld\n", commands->st_size);
}
