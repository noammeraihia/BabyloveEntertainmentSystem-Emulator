#include <stdio.h>
#include <stdlib.h>

#include "core/bes_core.h"
#include "app/bes_app.h"

#include <windows.h>
#include <conio.h>

void initCPU(bes6502CPU_t *CPU)
{
    besBinFile_t program = besLoadBinFile("cpu_test.bin");

    besWORD_t ramOffset = 0x8000;

    bes6502CPU_write(CPU, 0xFFFC, 0x00);
    bes6502CPU_write(CPU, 0xFFFD, 0x80);

    bes6502CPU_reset(CPU);

    for (besWORD_t i = 0; i < program.fileSize; i++)
    {
        bes6502CPU_write(CPU, ramOffset + i, program.bytes[i]);
    }
}

int main(int argc, char *argv[])
{
    bes_appInit();

    bes6502CPU_t CPU = bes6502CPU_create();

    initCPU(&CPU);

    besAppWindow_t window = besCreateAppWindow("Main", 75, 150, 0, 0, besCreateAppFramebuffer(100, 100, 1080, 760));

    bool isRunning = true;
    while (isRunning)
    {
        besAppWindowBeginFrame(&window);

        while (besAppWindowPollEvent(&window))
        {
            switch (window.event.type)
            {
            case SDL_KEYDOWN:
                if (window.event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                    do
                    {
                        bes6502CPU_clock(&CPU);
                    } while (!(CPU.cycles == 0));
                }
                break;
            case SDL_QUIT:
                isRunning = false;
                break;
            }
        }

        CPU.opcode = bes6502CPU_read(&CPU, CPU.PC);
        printf("Current instruction Name => %s\n", CPU.instructionTable[CPU.opcode].name);
        printf("Current instruction OpCode => %x\n", CPU.opcode);
        printf("Current instruction Cycles => %d\n", CPU.instructionTable[CPU.opcode].cycles);
        printf("Current location => %x\n", CPU.PC);

        printf("A => %x\n", CPU.A);
        printf("X => %x\n", CPU.X);
        printf("Y => %x\n\n\n", CPU.Y);

        printf("C => %d\n", bes6502CPU_getFlag(&CPU, BES_6502_PSF_C));
        printf("Z => %d\n", bes6502CPU_getFlag(&CPU, BES_6502_PSF_Z));
        printf("I => %d\n", bes6502CPU_getFlag(&CPU, BES_6502_PSF_I));
        printf("D => %d\n", bes6502CPU_getFlag(&CPU, BES_6502_PSF_D));
        printf("B => %d\n", bes6502CPU_getFlag(&CPU, BES_6502_PSF_B));
        printf("U => %d\n", bes6502CPU_getFlag(&CPU, BES_6502_PSF_U));
        printf("V => %d\n", bes6502CPU_getFlag(&CPU, BES_6502_PSF_V));
        printf("N => %d\n", bes6502CPU_getFlag(&CPU, BES_6502_PSF_N));

        printf("\n[");
        for (int i = 0; i < 8; i++)
        {
            besBYTE_t data = bes6502CPU_read(&CPU, i);
            printf(" %x ", data);
        }
        printf("]\n");

        besAppWindowEndFrame(&window);

        SDL_Delay(50);

        system("cls");
    }

    besFreeAppWindow(&window);

    return 0;
}