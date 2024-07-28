#ifndef BES_FILE_HANDLING
#define BES_FILE_HANDLING

#include <stdio.h>
#include <stdlib.h>

#include "bes_types.h"

#define BES_BINFILE_MAX_SIZE 0xFF

typedef struct s_besBinFile besBinFile_t;

struct s_besBinFile
{
    besBYTE_t *bytes;
    long fileSize;
};

besBinFile_t besLoadBinFile(const char *__filename);

#endif