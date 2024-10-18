#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "assembler.h"

int main()
{
    struct file_t file = {};

    OpenFiles(&file);

    WriteToFile(&file);

    fclose(file.byte_code_write);
    fclose(file.commands_file);

    return 0;
}

void WriteToFile(struct file_t* file)
{
    int arg = 0;
    while (fscanf(file->commands_file, "%s", file->command) != EOF) //TODO use onegin // make dir lib and stack in this
    {
        assert(file->command);

        //printf("command: %s\n", command);

        COMPILATION_ARG("push", PUSH);

        COMPILATION_ARG("jmp", JUMP);

        COMPILATION_ARG("jb", JB);

        COMPILATION_ARG("jbe", JBE);

        COMPILATION("sub", SUB);

        COMPILATION("div", DIV);

        COMPILATION("add", ADD);

        COMPILATION("mul", MUL);

        COMPILATION("dump", DUMP);

        COMPILATION("hlt", HLT);
    }
}

void OpenFiles(struct file_t* file)
{
    file->commands_file   = fopen(INPUT_COMMANDS, "r"); //TODO && directory asm
    file->byte_code_write = fopen(BYTE_CODE_W, "w");

    assert(file->commands_file);
    assert(file->byte_code_write);

    file->command = (char*) calloc(MAX_SIZE_COM, sizeof(char));

    assert(file->command);
}
