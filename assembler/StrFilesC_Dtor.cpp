#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "assembler.h"
#include "StrFilesC_Dtor.h"

void StrFilesCtor(struct assm* global_assm, struct stat* st_file)
{
    assert(global_assm);

    global_assm->commands_file   = fopen(INPUT_COMMANDS, "rb"); //TODO && directory asm
    global_assm->byte_code_write = fopen(BYTE_CODE_W, "w");

    assert(global_assm->commands_file);
    assert(global_assm->byte_code_write);

    global_assm->command = (char*) calloc((size_t)(st_file->st_size), sizeof(char)); //TODO use ctor for this

    assert(global_assm->command);
}

void StrFilesDtor(struct assm* global_assm)
{
    free(global_assm->command);

    fclose(global_assm->commands_file);
    fclose(global_assm->byte_code_write);
}

void InitStat(struct stat* st_file)
{
    assert(st_file);

    stat(INPUT_COMMANDS, st_file);

    printf("st_size = %ld\n", st_file->st_size);

    assert(st_file->st_size);
}
