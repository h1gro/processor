#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "assembler.h"

void FindLabel(struct assembler* assm)
{
    assert(assm);
    assert(assm->command);

    bool label_found = 0;

    for (int i = 0; i < NUMBER_OF_LABELS; i++)
    {
        assert(assm->labels[i].label);

        if (strcmp((const char*)assm->command, (const char*)assm->labels[i].label) == 0)
        {
            printf("\n\n addr label = %d!!!\n\n\n", assm->labels[i].addr);
            fprintf(assm->byte_code_write, "%d", assm->labels[i].addr);

            label_found = 1;
        }
    }

    if (label_found == 0)
    {
        for (int i = 0; i < NUMBER_OF_LABELS; i++)
        {
            if (assm->labels[i].addr == INVALID_ADDR)
            {
                printf("i am here\n");
                strcpy(assm->labels[i].label, (const char*)assm->command);

                assm->labels[i].addr = YARLY_ADDR;
                fprintf(assm->byte_code_write, "%d", assm->labels[i].addr);
                printf("from find label:"
                       "ip_mark = %d, addr = %d, mark = %s\n",
                        i, assm->labels[i].addr,
                        assm->labels[i].label);
                break;
            }
        }
    }
}

int LabelAssignment(struct assembler* assm)
{
    assert(assm->command);
    assert(assm->labels);

    if (assm->input_code[assm->index] == ':')
    {
        for (int i = 0; i < NUMBER_OF_LABELS; i++)
        {
            if ((assm->labels[i].addr == YARLY_ADDR) && (strcmp((const char*)assm->labels[i].label, (const char*)assm->command) == 0))
            {
                printf("хелоу епта\n");
                assm->labels[i].addr = assm->num_elem_file;
                printf("num el file = %d\n", assm->num_elem_file);
                printf("assm->labels[i].addr = %d\n", assm->labels[i].addr);
                printf("from label assignment:"
                       "ip_mark = %d, addr = %d, mark = %s\n",
                        i, assm->labels[i].addr,
                        assm->labels[i].label);

                return YEARLY_LABEL_ASSIGNED;
            }

            else if ((assm->labels[i].addr != YARLY_ADDR) && (strcmp((const char*)assm->labels[i].label, (const char*)assm->command) == 0))//TODO несколько ранних меток
            {
                return  YEARLY_LABEL_ASSIGNED;
            }
        }

        for (int i = 0; i < NUMBER_OF_LABELS; i++)
        {
            if (assm->labels[i].addr == INVALID_ADDR)
            {
                printf("а теперь епта\n");
                assm->labels[i].addr = assm->num_elem_file;

                strcpy(assm->labels[i].label, (const char*)assm->command);

                printf("from label assignment:"
                       "ip_mark = %d, addr = %d, mark = %s\n",
                        i, assm->labels[i].addr,
                        assm->labels[i].label);

                //assm->num_elem_file++;
                break;
            }
        }
    }

    else
    {
        return NOT_A_LABEL;
    }

    return NEW_LABEL_ASSIGNED;
}
