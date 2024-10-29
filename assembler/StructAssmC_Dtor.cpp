#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "assembler.h"
#include "StructAssmC_Dtor.h"

static const char* INPUT_COMMANDS = "commands.txt";
static const char* BYTE_CODE_W = "../byte_code.txt";

void StructAssmCtor(struct assm* global_assm, struct stat* st_file)
{
    assert(global_assm);

    global_assm->commands_file   = fopen(INPUT_COMMANDS, "rb");
    global_assm->byte_code_write = fopen(BYTE_CODE_W, "w");

    assert(global_assm->commands_file);
    assert(global_assm->byte_code_write);

    global_assm->command = (char*) calloc((size_t)(st_file->st_size), sizeof(char));
    global_assm->buffer = (char*) calloc((size_t)(st_file->st_size) + 1, sizeof(char));

    assert(global_assm->command);
    assert(global_assm->buffer);
}

void StructAssmDtor(struct assm* global_assm)
{
    free(global_assm->command);
    free(global_assm->buffer);

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
