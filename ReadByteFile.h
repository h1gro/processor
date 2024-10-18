#ifndef READ_BYTE_FILE
#define READ_BYTE_FILE

static const char* BYTE_CODE_R = "byte_code.txt";

enum consts
{
    NUM_ARGS_PUSH = 1,
    NUM_ARGS_JMP  = 1,
};

void ReadByteFile(struct spu_t* spu, struct stat* commands);
void FillingCode(struct spu_t* spu, FILE* mach_code_read);
void InitStat(struct stat* commands);
void LaunchCommand(struct stat* commands, struct spu_t* spu);

#endif

