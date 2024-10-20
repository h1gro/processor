#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "assembler.h"
#include "StrFilesC_Dtor.h"

void StrFilesCtor(struct file_t* file)
{
    assert(file);

    file->commands_file   = fopen(INPUT_COMMANDS, "r"); //TODO && directory asm
    file->byte_code_write = fopen(BYTE_CODE_W, "w");

    assert(file->commands_file);
    assert(file->byte_code_write);

    file->command = (char*) calloc(MAX_SIZE_COM, sizeof(char)); //TODO use ctor for this

    assert(file->command);
}

void StrFilesDtor(struct file_t* file)
{
    free(file->command);

    fclose(file->commands_file);
    fclose(file->byte_code_write);
}
