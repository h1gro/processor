#ifndef ASSEMBLER
#define ASSEMBLER

const int MAX_SIZE_COM    = 15;
const int NUMBER_OF_MARKS = 10;

struct label
{
    int addr;
    char* label;
};

struct assm
{
    FILE* commands_file;
    FILE* byte_code_write;
    char* command;
    int size_label_arr;
    struct label labels[NUMBER_OF_MARKS];
    char* buffer;
    size_t buffer_size;
};

int DefineReg(struct assm* global_assm);
void CompileCommands(struct assm* global_assm, struct stat* st_file);
void InitStat(struct stat* st_file);

#endif
