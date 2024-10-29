#ifndef READ_BYTE_FILE
#define READ_BYTE_FILE

static const char* BYTE_CODE_R = "../byte_code.txt";

void ReadByteFile(struct spu_t* spu);
void FillingCode(struct spu_t* spu, FILE* mach_code_read);
void InitStat(struct stat* commands);

#endif

