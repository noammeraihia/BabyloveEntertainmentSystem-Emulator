#include <stdio.h>
#include <stdlib.h>

#include "CPU/bes_6502cpu.h"

int main(int argc, char* argv[])
{
    printf("Hello BES !\n");

    bes6502CPU_t CPU = bes6502CPU_create();
    besBus_t bus = besBus_create(&CPU);

    bes6502CPU_write(&CPU, 0xf0f0, 0xF9);
    printf("%x\n", bes6502CPU_read(&CPU, 0xf0f0));

    return 0;
}