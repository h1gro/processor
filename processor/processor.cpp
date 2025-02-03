#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../lib/stack/global.h"
#include "processor.h"

int main()
{
    struct spu_t spu     = {};
    struct stat commands = {};

    InitStat(&commands);
    SpuCtor(&spu, &commands);

    ReadByteFile(&spu);

    LaunchCommand(&spu);

//     for (int i = 0; i < 21; i++)
//     {
//         for (int j = 0; j < 21; j++)
//         {
//             printf("%d ", spu.ram[i * 20 + j]);
// //             if ((spu.ram + (i * 10 + j)) == 0)
// //             {
// //                 printf("*");
// //             }
// //
// //             else
// //             {
// //                 printf("0");
// //             }
//         }
//         printf("\n");
//     }

    SpuDtor(&spu);
    return 0;
}


