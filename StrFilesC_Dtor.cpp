#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "assembler.h"
#include "StrFilesC_Dtor.h"

void StrFilesCtor(struct file_t* file, struct stat* st_file)
{
    assert(file);

    file->commands_file   = fopen(INPUT_COMMANDS, "rb"); //TODO && directory asm
    file->byte_code_write = fopen(BYTE_CODE_W, "w");

    assert(file->commands_file);
    assert(file->byte_code_write);

    file->command = (char*) calloc((size_t)(st_file->st_size), sizeof(char)); //TODO use ctor for this

    assert(file->command);
}

void StrFilesDtor(struct file_t* file)
{
    free(file->command);

    fclose(file->commands_file);
    fclose(file->byte_code_write);
}

void InitStat(struct stat* st_file)
{
    assert(st_file);

    stat(INPUT_COMMANDS, st_file);

    printf("st_size = %ld\n", st_file->st_size);

    assert(st_file->st_size);
}
