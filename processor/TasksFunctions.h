#ifndef _TASKS_FUNCTIONS_
#define _TASKS_FUNCTIONS_

static const char* SQUARE_EQUATION = "../square_equation.txt";
static const char* PROC_CIRCLE     = "../Circle.txt";

const double POISON_ROOT    = -153.153;
const double INFINITY_ROOTS = 6892.363;
const double NO_ROOTS       = 513.513;


int IsEqual              (double elem1, double elem2);
void DrowCircle           (struct spu_t* spu);

double SolveLinear       (struct spu_t* spu);

void SolveSquare         (struct spu_t* spu, FILE* equation);
void WriteSquareEquation (struct spu_t* spu, double x1, double x2, FILE* equation);

#endif
