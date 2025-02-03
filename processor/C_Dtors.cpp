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
    spu->registers = (double*) calloc(NUM_REGISTERS, sizeof(double));

    assert(spu->code);
    assert(spu->registers);

    StackCtor(&spu->stk);
    StackCtor(&spu->ret);
    RamCtor(spu);

    spu->ip = 0;
}

void SpuDtor(struct spu_t* spu)
{
    assert(spu);

    spu->ip = 0;

    StackDtor(&spu->stk);
    StackDtor(&spu->ret);
    RamDtor(spu);

    free(spu->code);
    free(spu->registers);
}

void RamCtor(struct spu_t* spu)
{
    assert(spu);

    spu->ram = (int*) calloc(RAM_CAPASITY, sizeof(int));

    assert(spu->ram);
}

void RamDtor(struct spu_t* spu)
{
    assert(spu);

    free(spu->ram);
}

void InitStat(struct stat* commands)
{
    assert(commands);

    stat(BYTE_CODE_R, commands);

    assert(commands->st_size);

    printf("st_size = %ld\n", commands->st_size);
}
