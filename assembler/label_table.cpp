#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "assembler.h"
#include "label_table.h"
#include "StructAssmC_Dtor.h"

void FindLabel(struct assembler* assm)
{
    assert(assm);
    assert(assm->command);
    assert(assm->size_label_arr);

    for (int i = 0; i < assm->size_label_arr; i++)
    {
        assert(assm->labels[i].label);
        assert(assm->labels[i].addr != INVALID_ADDR);

        if (strcmp((const char*)assm->command, (const char*)assm->labels[i].label) == 0)
        {
            printf("\n\n addr label = %d!!!\n\n\n", assm->labels[i].addr);
            fprintf(assm->byte_code_write, "%d", assm->labels[i].addr);
        }

        else
        {
            printf("\n<<<<<<unknown mark!>>>>>>\n\n");
        }
    }
}

void LabelAssignment(struct assembler* assm)
{
    assert(assm->command);
    assert(assm->labels);

    assert(assm->labels[assm->size_label_arr].addr == -1);
    assert(assm->labels[assm->size_label_arr].label);

    if (assm->input_code[assm->index] == ':')
    {
        assm->labels[assm->size_label_arr].addr  = assm->num_elem_file;

        strcpy(assm->labels[assm->size_label_arr].label, (const char*)assm->command);

        printf("ip_mark = %d, addr = %d, mark = %s\n",
                assm->size_label_arr, assm->labels[assm->size_label_arr].addr,
                assm->labels[assm->size_label_arr].label);

        assm->num_elem_file++;
        assm->size_label_arr++;
    }
}
