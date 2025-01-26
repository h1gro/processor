#ifndef _ASSEMBLER_
#define _ASSEMBLER_

const int MAX_SIZE_COM    = 15;
const int NUMBER_OF_MARKS = 10;

struct label
{
    int   addr;
    char* label;
};

struct assembler
{
    FILE* commands_file;
    FILE* byte_code_write;
    char* command;
    char* input_code;
    int   index;
    int   capacity;
    int   size_label_arr;
    int   last_command;
    int   num_elem_file;
    label labels[NUMBER_OF_MARKS];
};

int  DefineReg       (struct assembler* assm);

void InitStat        (struct stat* st_file);
void CompileCommands (struct assembler* assm);

#endif
