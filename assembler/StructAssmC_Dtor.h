#ifndef _STRFILESC_DTOR_
#define _STRFILESC_DTOR_

const int INVALID_ADDR = -1;
const int NULL_ADDR    = 0;

enum funcs
{
    CTOR = 89,
    DTOR = 99,
};

void LabelsCtor          (struct assembler* assm);
void LabelsDtor          (struct assembler* assm);
void StructAssmDtor      (struct assembler* assm);
void StructAssmCtor      (struct assembler* assm, struct stat* st_file);
void FillingStructLabels (struct assembler* assm, int poison, funcs func_call);

#endif

