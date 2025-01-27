#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#include "../lib/stack/global.h"
#include "processor.h"

void ReadByteFile(struct spu_t* spu)
{
    assert(spu);
    assert(spu->registers);
    assert(spu->code);

    FILE* byte_code_read = fopen(BYTE_CODE_R, "rb");

    assert(byte_code_read);

    FillingCode(spu, byte_code_read);

    fclose(byte_code_read);
}

void FillingCode(struct spu_t* spu, FILE* byte_code_read)
{
    assert(spu);
    assert(byte_code_read);
    assert(spu->code);
    assert(spu->ip >= 0);

    while(!feof(byte_code_read))
    {
        fscanf(byte_code_read, "%d", &spu->code[spu->ip]);
        printf("%d\n", spu->code[spu->ip]);

        spu->code_elems++;
        spu->ip++;
    }
}
