#include <stdio.h>
#include <stdlib.h>

#include "core/bes_core.h"
#include "app/bes_app.h"

#include <windows.h>

void initCPU(bes6502CPU_t *CPU)
{
    besBinFile_t program = besLoadBinFile("cpu_test.bin");

    besWORD_t ramOffset = 0x8000;

    for (int i = 0; i < program.fileSize; i++)
    {
        bes6502CPU_write(CPU, ramOffset + i, program.bytes[i]);
    }

    free(program.bytes);

    bes6502CPU_write(CPU, 0xFFFC, 0x00);
    bes6502CPU_write(CPU, 0xFFFD, 0x80);
}

int main(int argc, char *argv[])
{
    bes_appInit();

    bes6502CPU_t CPU = bes6502CPU_create();
    besBus_t bus = besBus_create(&CPU);

    initCPU(&CPU);

    besAppWindow_t window = besCreateAppWindow("Main", 1280, 960, 0, 0, besCreateAppFramebuffer(100, 100, 1080, 760));

    int x = 50;
    int y = 50;

    bool isRunning = true;
    while (isRunning)
    {
        besAppWindowBeginFrame(&window);

        while (besAppWindowPollEvent(&window))
        {
            switch (window.event.type)
            {
            case SDL_KEYDOWN:
                if (window.event.key.keysym.scancode == SDL_SCANCODE_A)
                {
                    window.isCOShown = false;
                }
                if (window.event.key.keysym.scancode == SDL_SCANCODE_C)
                {
                    window.isCOShown = true;
                }
                break;
            case SDL_QUIT:
                isRunning = false;
                break;
            }
        }

        besAppWindowEndFrame(&window);
    }

    besFreeAppWindow(&window);

    return 0;
}