#include <stdio.h>
#include <stdlib.h>

#include "core/CPU/bes_6502cpu.h"
#include "core/CPU/bes_6502cpu_common.h"
#include "core/utils/bes_fileHandling.h"
#include "app/bes_app.h"

#include <windows.h>

int main(int argc, char *argv[])
{
    bes_appInit();

    bes6502CPU_t CPU = bes6502CPU_create();
    besBus_t bus = besBus_create(&CPU);

    besBinFile_t program = besLoadBinFile("cpu_test.bin");

    besWORD_t ramOffset = 0x8000;

    for (int i = 0; i < program.fileSize; i++)
    {
        bes6502CPU_write(&CPU, ramOffset + i, program.bytes[i]);
    }

    free(program.bytes);

    bes6502CPU_write(&CPU, 0xFFFC, 0x00);
    bes6502CPU_write(&CPU, 0xFFFD, 0x80);

    return 0;
}