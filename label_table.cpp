#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "assembler.h"
#include "label_table.h"

void LabelsCtor(struct label* labels)
{
    assert(labels);

    for(int i = 0; i < NUMBER_OF_MARKS; i++)
    {
        labels[i].addr = - 1;
        labels[i].mark = {};
    }
}

void LabelsDtor(struct label* labels)
{
    assert(labels);

    for(int i = 0; i < NUMBER_OF_MARKS; i++)
    {
        labels[i].addr = - 1;
        labels[i].mark = {};
    }
}

void FindMark(struct label* labels, struct file_t* file, int command, int ip_mark)
{
    for(int i = 0; i < ip_mark; i++)
    {
        if (strcmp((const char*)file->command, (const char*)labels[i].mark) == 0)
        {
            fprintf(file->byte_code_write, "%d %d\n", command, labels[i].addr);
        }

        else
        {
            printf("\n<<<<<<unknown mark!>>>>>>\n\n");
        }
    }
}
