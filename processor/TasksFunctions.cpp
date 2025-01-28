#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "../lib/stack/global.h"
#include "processor.h"
#include "TasksFunctions.h"

void SolveSquare(struct spu_t* spu, FILE* equation)
{
    assert(spu);
    assert(equation);

    // D = b^2 - 4ac
    double D = spu->registers[1] * spu->registers[1] - 4 * spu->registers[0] * spu->registers[2];

    if (IsEqual(spu->registers[0], 0))
    {
        WriteSquareEquation(spu, SolveLinear(spu), POISON_ROOT, equation);
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

            WriteSquareEquation(spu, x1, x2, equation);
        }
        else
        {
            WriteSquareEquation(spu, NO_ROOTS, NO_ROOTS, equation);
        }
    }
}

double SolveLinear(struct spu_t* spu)
{
        assert(spu);

        double x1 = 0;

        if (IsEqual(spu->registers[1], 0))
        {
            if (IsEqual(spu->registers[2], 0))
            {
                printf("infinity roots\n");

                return INFINITY_ROOTS;
            }
            else
            {
                printf("no roots\n");

                return NO_ROOTS;
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

            return x1;
        }
}

int IsEqual(double elem1, double elem2)
{
    return (fabs(elem1 - elem2) <= EPSILON);
}

void WriteSquareEquation(struct spu_t* spu, double x1, double x2, FILE* equation)
{
    assert(spu);
    assert(equation);

    static int first_equation = 1;

    if (first_equation)
    {
        fprintf(equation, "(a) * x^2 + (b) * x + (c) = 0\n"
                          "-----------------------------\n");

        first_equation = 0;
    }

    fprintf(equation, "(%lg) * x^2 + (%lg) * x + (%lg) = 0\n", spu->registers[0], spu->registers[1], spu->registers[2]);

    if (IsEqual(x1, INFINITY_ROOTS))
    {
        fprintf(equation, "Infinity roots\n");
    }

    else if (IsEqual(x1, NO_ROOTS))
    {
        fprintf(equation, "No roots\n");
    }

    else if (IsEqual(x2, POISON_ROOT))
    {
        fprintf(equation, "x1 = %lg\n", x1);
    }

    else
    {
        fprintf(equation, "x1 = %lg\nx2 = %lg\n", x1, x2);
    }

    fprintf(equation, "------------------------------\n");
}

