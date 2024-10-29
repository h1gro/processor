#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "assembler.h"
#include "label_table.h"

void LabelsCtor(struct assm* global_assm)
{
    assert(global_assm);

    int poison = INVALID_ADDR;

    FillingStructLabels(global_assm, poison);
}

void LabelsDtor(struct assm* global_assm)
{
    assert(global_assm);

    int poison = NULL_ADDR;

    FillingStructLabels(global_assm, poison);
}

void FindMark(struct assm* global_assm, int command)
{
    for(int i = 0; i < global_assm->size_label_arr; i++)
    {
        if (strcmp((const char*)global_assm->command, (const char*)global_assm->labels[i].label) == 0)
        {
            printf("\n\n addr label = %d!!!\n\n\n", global_assm->labels[i].addr);
            fprintf(global_assm->byte_code_write, "%d %d\n", command, global_assm->labels[i].addr);
        }

        else
        {
            printf("\n<<<<<<unknown mark!>>>>>>\n\n");
        }
    }
}

void FillingStructLabels(struct assm* global_assm, int poison)
{
    for(int i = 0; i < NUMBER_OF_MARKS; i++)
    {
        global_assm->labels[i].addr = poison;
        global_assm->labels[i].label = {};
    }
}
