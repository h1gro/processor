#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "../lib/stack/global.h"
#include "processor.h"
#include "TasksFunctions.h"

void SolveSquare(struct spu_t* spu)
{
    assert(spu);

    // D = b^2 - 4ac
    double D = spu->registers[1] * spu->registers[1] - 4 * spu->registers[0] * spu->registers[2];

    if (IsEqual(spu->registers[0], 0))
    {
        SolveLinear(spu);
    }

    else
    {
        if (D >= 0)
        {
            double sqrt_D = sqrt(D);

            // x12 = (-b +- sqrt(D)) / 2a
            double x1 = ((-1) * spu->registers[1] + sqrt_D) / (2 * spu->registers[0]);
            double x2 = ((-1) * spu->registers[1] - sqrt_D) / (2 * spu->registers[0]);

            if (IsEqual(x1, x2))
            {
                printf("x1 = %lg\n", x1);

                StackPush(&spu->stk, x1);
            }
            else
            {
                StackPush(&spu->stk, x1);
                StackPush(&spu->stk, x2);

                printf("x1 = %lg\nx2 = %lg\n", x1, x2);
            }
        }
        else
        {
            printf("no roots\n");
        }
    }
}

void SolveLinear(struct spu_t* spu)
{
        double x1 = 0;

        if (IsEqual(spu->registers[1], 0))
        {
            if (IsEqual(spu->registers[2], 0))
            {
                printf("infinity roots\n");
            }
            else
            {
                printf("no roots\n");
            }
        }

        else
        {
            if (IsEqual(spu->registers[2] / spu->registers[1], 0))
            {
                x1 = 0;
            }
            else
            {
                x1 = -spu->registers[2] / spu->registers[1];
            }

            StackPush(&spu->stk, x1);

            printf("x1 = %lg\n", x1);
        }
}

int IsEqual(double elem1, double elem2)
{
    return (fabs(elem1 - elem2) <= EPSILON);
}
