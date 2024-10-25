#ifndef LABEL_TABLE
#define LABEL_TABLE

const int INVALID_ADDR = - 1;
const int NULL_ADDR    = 0;

void LabelsCtor(struct assm* global_assm);
void LabelsDtor(struct assm* global_assm);
void FindMark(struct assm* global_assm, int command);
void FillingStructLabels(struct assm* global_assm, int poison);

#endif
