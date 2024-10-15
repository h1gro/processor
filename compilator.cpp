#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "compilator.h"

int main()
{
    FILE *inp_commands = fopen(INPUT_COMMANDS, "r");
    FILE *mach_code_write = fopen(MACHINE_CODE, "w");

    assert(inp_commands);

    char* command = (char*) calloc(16, sizeof(char));
    int arg = 0;

    while (fscanf(inp_commands, "%s", command) != EOF)
    {
        //printf("command: %s\n", command);
        const char* command0 = command;
        if (stricmp(command0, "push") == 0)
        {
            fscanf(inp_commands, "%d", &arg);
            fprintf(mach_code_write, "%d %d\n", 1, arg);
        }

        if (stricmp(command0, "sub") == 0)
        {
            fprintf(mach_code_write, "%d\n", 2);
        }

        if (stricmp(command0, "div") == 0)
        {
            fprintf(mach_code_write, "%d\n", 3);
        }

        if (stricmp(command0, "add") == 0)
        {
            fprintf(mach_code_write, "%d\n", 4);
        }

        if (stricmp(command0, "mul") == 0)
        {
            fprintf(mach_code_write, "%d\n", 5);
        }

        if (stricmp(command0, "dump") == 0)
        {
            fprintf(mach_code_write, "%d\n", 11);
        }

        if (stricmp(command0, "hlt") == 0)
        {
            fprintf(mach_code_write, "%d\n", 0);
        }
    }

    assert(mach_code_write);

    fclose(mach_code_write);
    fclose(inp_commands);
    return 0;
}
