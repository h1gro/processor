#ifndef ASSEMBLER
#define ASSEMBLER

const int MAX_SIZE_COM    = 15;
const int NUMBER_OF_MARKS = 10;

struct label
{
    int addr;
    char* mark;
};

struct assm //TODO rename stuct
{
    FILE *commands_file;
    FILE *byte_code_write;
    char* command;
    int ip_label;
    struct label labels[NUMBER_OF_MARKS];
};

int DefineReg(struct assm* global_assm);
void CompileCommands(struct assm* global_assm, struct stat* st_file);
void StrFilesCtor(struct assm* global_assm, struct stat* st_file); //TODO rename
void StrFilesDtor(struct assm* global_assm); //TODO rename
void InitStat(struct stat* st_file);
void DefineArg(struct assm* global_assm, int number_command);

#endif
