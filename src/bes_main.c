#include <stdio.h>
#include <stdlib.h>

#include "core/bes_core.h"
#include "app/bes_app.h"

#include <windows.h>
#include <conio.h>

void initCPU(bes6502CPU_t *CPU)
{
    besBinFile_t program = besLoadBinFile("emul_bin/cpu_test.bin");

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

    bool clocked = false;
    bool isRunning = true;
    while (isRunning)
    {
        clocked = false;
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
                    clocked = true;
                }
                else if (window.event.key.keysym.scancode == SDL_SCANCODE_R)
                {
                    bes6502CPU_reset(&CPU);
                }
                break;
            case SDL_QUIT:
                isRunning = false;
                break;
            }
        }

        besAppWindowEndFrame(&window);

        if (clocked)
        {
            system("cls");
            bes6502CPU_crenderinfo(&CPU);
            bes6502CPU_crendermem(&CPU, 0x0000, 0x000F, 16);
        }
    }

    besFreeAppWindow(&window);

    return 0;
}