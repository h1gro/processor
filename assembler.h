#ifndef ASSEMBLER
#define ASSEMBLER

const int MAX_SIZE_COM = 10;

#define COMPILATION(COMMAND_NAME, COMMAND_ENUM)                        \
do {                                                                   \
    if (strcmp((const char*)file->command, COMMAND_NAME) == 0)        \
    {                                                                  \
        fprintf(file->byte_code_write, "%d\n", COMMAND_ENUM);          \
    }                                                                  \
} while(0)

#define COMPILATION_ARG(COMMAND_NAME, COMMAND_ENUM)                    \
do {                                                                   \
    if (strcmp((const char*)file->command, COMMAND_NAME) == 0)        \
    {                                                                  \
        fscanf(file->commands_file, "%d", &arg);                       \
        fprintf(file->byte_code_write, "%d %d\n", COMMAND_ENUM, arg);  \
    }                                                                  \
} while(0) //TODO COMPILATION_ARG && use func check args

enum comands
{
    HLT  = 0,
    PUSH = 1,
    SUB  = 2,
    DIV  = 3,
    ADD  = 4,
    MUL  = 5,
    OUT  = 6,
    IN   = 7,
    SQRT = 8,
    SIN  = 9,
    COS  = 10,
    DUMP = 11,
    JUMP = 12,
    JB   = 13,
    JBE  = 14,
};

struct file_t
{
    FILE *commands_file;
    FILE *byte_code_write;
    char* command;
};

void WriteToFile(struct file_t* file);
void StrFilesCtor(struct file_t* file);
void StrFilesDtor(struct file_t* file);

#endif
