#ifndef LABEL_TABLE
#define LABEL_TABLE

void LabelsCtor(struct label* labels);
void LabelsDtor(struct label* labels);
void FindMark(struct label* labels, struct file_t* file, int command, int ip_mark);

#endif
