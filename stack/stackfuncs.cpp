#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "global.h"

void StackCtor(struct stack_t *stk)
{
    assert(stk);

    stk->output = fopen(DUMP_FILE, "w+");

    #ifdef DEBUG
        stk->canary1 = CANARY;
        stk->canary2 = CANARY;
    #endif
    //printf("canary1 = %lg, canary2 = %lg\n", stk->canary1, stk->canary2);

    stk->size = 0;
    stk->error_code = NO_ERRORS;
    stk->capacity = CAPACITY;
    stk->data = (stackelem_t*) calloc((size_t)(stk->capacity + NUM_CANARIES_BUF), sizeof(stackelem_t)) + NUM_CANARIES_IN_LEFT;

    FillingDataPoison(stk->data, stk->capacity - stk->size);

    //printf("canary1 = %lg, canary2 = %lg\n", stk->canary1, stk->canary2);
    stk->data[-1] = CANARY;
    stk->data[stk->capacity] = CANARY;

    assert(stk->data);
    assert(stk->capacity);

    STACK_CHECK(stk);
}

void StackDtor(struct stack_t *stk)
{
    assert(stk);
    assert(stk->data);

    stk->capacity = 0;

    stk->size = 0;

    fclose(stk->output);
    free(stk->data - NUM_CANARIES_IN_LEFT);
}

void FillingDataPoison(stackelem_t *data, int num_el_poison)
{
    for (int i = 0; i <= num_el_poison; i++)
    {
        data[i] = POISON;
    }
}

void StackPush(struct stack_t *stk, stackelem_t elem)
{
    assert(stk);
    assert(stk->data);
    STACK_CHECK(stk);

    //fprintf(stk->output, "\n\nfirst DUMP\n");

    //StackDump(stk, __func__, __FILE__, __LINE__, STACK_PUSH);

    fprintf(stk->output, "push elem = %lg\n", elem);
    int pop_or_push = STACK_PUSH;
    ResizeIf(stk, pop_or_push);

    stk->data[stk->size] = elem;
    stk->size++;

    assert(stk->capacity);
    assert(stk->size);

    fprintf(stk->output, "second DUMP\n");
    StackDump(stk, __func__, __FILE__, __LINE__, STACK_PUSH);

    STACK_CHECK(stk);

}

stackelem_t StackPop(struct stack_t *stk, const char* proc_func, int proc_line)
{
    printf("\n\nStack pop was called from %s:%d\n\n", proc_func, proc_line);

    STACK_CHECK(stk);

    //fprintf(stk->output, "\n\nfirst POP\n");

    //StackDump(stk, __func__, __FILE__, __LINE__, STACK_POP);

    fprintf(stk->output, "pop elem = %lg\n", stk->data[stk->size - 1]);
    stackelem_t discared_elem = stk->data[stk->size - 1];
    stk->data[stk->size - 1] = POISON;

    int pop_or_push = STACK_POP;
    ResizeIf(stk, pop_or_push);

    stk->size--;
    STACK_CHECK(stk);

    printf("discared_elem = %lg\n", discared_elem);
    fprintf(stk->output, "second POP\n");

    StackDump(stk, __func__, __FILE__, __LINE__, STACK_POP);
    fprintf(stk->output, "discared_elem = %lg\n\n", discared_elem);
    return discared_elem;
}

void ResizeIf(struct stack_t *stk, int pop_or_push)
{
    if (pop_or_push == STACK_PUSH && stk->size == stk->capacity)
    {
        stk->data[stk->capacity] = POISON;
        stk->capacity = stk->capacity * CAPAC_RESIZE;
        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, (size_t)(stk->capacity + NUM_CANARIES_BUF) * sizeof(stackelem_t)) + NUM_CANARIES_IN_LEFT;

        FillingDataPoison(stk->data + stk->size, stk->capacity - stk->size);

        stk->data[stk->capacity] = CANARY;
    }

    if (pop_or_push == STACK_POP && stk->size * CAPAC_RESIZE + CAPAC_SHIFT < stk->capacity)
    {
        stk->capacity = stk->capacity / CAPAC_RESIZE;

        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, (size_t)(stk->capacity + NUM_CANARIES_BUF) * sizeof(stackelem_t)) + NUM_CANARIES_IN_LEFT;

        stk->data[stk->capacity] = CANARY;
    }
}

int CheckForErrors(struct stack_t *stk)
{
    #ifdef LEVEL_OF_PROTECTION

        assert(stk);
        assert(stk->data);
        assert(stk->capacity);
        assert(stk->size >= 0);

        assert(fabs(stk->data[-1] - CANARY)            < EPSILON);
        assert(fabs(stk->data[stk->capacity] - CANARY) < EPSILON);


        #ifdef DEBUG
            assert(fabs(stk->canary1 - CANARY) < EPSILON);
            assert(fabs(stk->canary2 - CANARY) < EPSILON);
        #endif

    #endif

    #ifdef DEBUG
        if (fabs(stk->canary1 - CANARY) > EPSILON)
        {
            stk->error_code = CANARY1_STR_ERROR;
            return stk->error_code;
        }

        if (fabs(stk->canary2 - CANARY) > EPSILON)
        {
            stk->error_code = CANARY2_STR_ERROR;
            return stk->error_code;
        }
    #endif

    if (stk == NULL)
    {
        stk->error_code = STK_ERROR;
        return stk->error_code;
    }

    if (stk->data == NULL)
    {
        stk->error_code = CTOR_ERROR;
        return stk->error_code;
    }

    if (stk->capacity == 0)
    {
        stk->error_code = CAPACITY_ERROR;
        return stk->error_code;
    }

    if (stk->size < 0)
    {
        stk->error_code = SIZE_ERROR;
        return stk->error_code;
    }

    if (stk->size > stk->capacity)
    {
        stk->error_code = PUSH_ERROR;
        return stk->error_code;
    }

    if (fabs(stk->data[-1] - CANARY) > EPSILON)
    {
        stk->error_code = CANARY1_BUF_ERROR;
        return stk->error_code;
    }

    if (fabs(stk->data[stk->capacity] - CANARY) > EPSILON)
    {
        stk->error_code = CANARY2_BUF_ERROR;
        return stk->error_code;
    }

    return NO_ERRORS;
}

int StackCheck(struct stack_t *stk, const char* file, int line, const char* func)
{
    if (CheckForErrors(stk) == NO_ERRORS)
    {
        return 0;
    }

    int dump_call = ERROR_PRINT;
    StackDump(stk, func, file, line, dump_call);

    return 1;
}

void StackDump(struct stack_t *stk, const char* func, const char* file, int line, int dump_call)
{
    assert(stk);
    assert(stk->data);

    #ifdef DEBUG

        assert(stk->file);
        assert(stk->func);
        assert(stk->name);

        fprintf(stk->output, "called from %s:%d %s\n"
                        "name %s born at %s:%d(%s)\n",
                        func, line, file, stk->name,
                        func, line, file);

        if(dump_call == ERROR_PRINT)
        {
            StackErrorOutput(stk);
        }
    #endif

    fprintf(stk->output, "size %d\n"
                    "capacity %d\nData:\n",
                    stk->size, stk->capacity);

    for (int i = -1; i < stk->capacity + NUM_CANARIES_IN_RIGHT; i++)
    {
        if (fabs(stk->data[i] - POISON) < EPSILON)
        {
            fprintf(stk->output, "data [%d] = %lg (POISON)\n", i, (stk->data)[i]);
        }
        else if (fabs(stk->data[i] - CANARY) < EPSILON)
        {
            fprintf(stk->output, "data [%d] = %lg (CANARY)\n", i, (stk->data)[i]);
        }
        else
        {
            fprintf(stk->output, "data [%d] = %lg\n", i, (stk->data)[i]);
        }
    }

    fprintf(stk->output, "\n");
}

void StackErrorOutput(struct stack_t *stk)
{
    switch(stk->error_code)
    {
    case PUSH_ERROR:        fprintf(stk->output, "\n<<<<<<<<<Error in stackpush\n\n");
                            break;

    case CTOR_ERROR:        fprintf(stk->output, "\n<<<<<<<<<Error in ctor\n\n");
                            break;

    case STK_ERROR:         fprintf(stk->output, "\n<<<<<<<<<Error in struct\n\n");
                            break;

    case CAPACITY_ERROR:    fprintf(stk->output, "\n<<<<<<<<<Error in capacity\n\n");
                            break;

    case SIZE_ERROR:        fprintf(stk->output, "\n<<<<<<<<<Error in size\n\n");
                            break;

    case CANARY1_BUF_ERROR: fprintf(stk->output, "\n<<<<<<<<<Error first canary in buffer\n\n");
                            break;

    case CANARY2_BUF_ERROR: fprintf(stk->output, "\n<<<<<<<<<Error second canary in buffer\n\n");
                            break;

    case CANARY1_STR_ERROR: fprintf(stk->output, "\n<<<<<<<<<Error first canary in struct\n\n");
                            break;

    case CANARY2_STR_ERROR: fprintf(stk->output, "\n<<<<<<<<<Error second canary in strucr\n\n");
                            break;

    default:                fprintf(stk->output, "\n<<<<<<<<<Unknown error\n\n");
    }
}
