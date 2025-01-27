#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "assembler.h"

static const char* INPUT_COMMANDS = "commands.txt";
static const char* BYTE_CODE_W = "../byte_code.txt";

void StructAssmCtor(struct assembler* assm, struct stat* st_file)
{
    assert(assm);

    assm->commands_file   = fopen(INPUT_COMMANDS, "rb");
    assm->byte_code_write = fopen(BYTE_CODE_W, "w");

    assert(assm->commands_file);
    assert(assm->byte_code_write);

    assm->input_code = (char*) calloc((size_t)(st_file->st_size), sizeof(char));

    assert(assm->input_code);

    assm->capacity = fread(assm->input_code, sizeof(char), st_file->st_size, assm->commands_file);

    for (int i = 0; i < st_file->st_size; i++)
    {
        if ((assm->input_code[i] != '\n') && (assm->input_code[i] != '\r') && (assm->input_code[i] != '\0') && (assm->input_code[i] != ' '))
        {
            printf("%c", assm->input_code[i]);
        }
    }

    printf("\n");
}

void StructAssmDtor(struct assembler* assm)
{
    free(assm->input_code);

    fclose(assm->commands_file);
    fclose(assm->byte_code_write);
}

void InitStat(struct stat* st_file)
{
    assert(st_file);

    stat(INPUT_COMMANDS, st_file);

    printf("st_size = %ld\n", st_file->st_size);

    assert(st_file->st_size);
}

void LabelsCtor(struct assembler* assm)
{
    assert(assm);
    assert(assm->labels);

    int poison = INVALID_ADDR;

    FillingStructLabels(assm, poison, CTOR);
}

void LabelsDtor(struct assembler* assm)
{
    assert(assm);
    assert(assm->labels);

    int poison = NULL_ADDR;

    FillingStructLabels(assm, poison, DTOR);
}

void FillingStructLabels(struct assembler* assm, int poison, funcs func_call)
{
    if (func_call == CTOR)
    {
        for (int i = 0; i < NUMBER_OF_MARKS; i++)
        {
            assm->labels[i].addr  = poison;

            assm->labels[i].label = (char*) calloc(MAX_SIZE_COM, sizeof(char));
        }
    }

    else if (func_call == DTOR)
    {
        for (int i = 0; i < NUMBER_OF_MARKS; i++)
        {
            assm->labels[i].addr  = poison;

            free(assm->labels[i].label);
        }
    }
}
