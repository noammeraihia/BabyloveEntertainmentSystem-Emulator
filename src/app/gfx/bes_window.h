#ifndef BES_WINDOW_h
#define BES_WINDOW_h

#include <stdio.h>
#include <stdlib.h>

#include <thirdparty/SDL2/SDL.h>
#include <thirdparty/c-logger/logger.h>

#include "bes_types.h"

typedef struct s_besAppWindow besAppWindow_t;
typedef struct s_besAppFramebuffer besAppFramebuffer_t;

struct s_besAppFramebuffer
{
    int x, y;
    int width, height;
    SDL_Rect destRect;
    SDL_Texture *handle;
    besDWORD_t *pixelsData;
};

struct s_besAppWindow
{
    SDL_Window *handle;
    SDL_Renderer *renderer;
    int width, height;

    SDL_Event event;

    besAppFramebuffer_t coreOutput;
    bool isCOShown;
};

besAppWindow_t besCreateAppWindow(const char *__name, int __width, int __height, SDL_WindowFlags __wF, SDL_RendererFlags __rF, besAppFramebuffer_t __coreOutput);
besAppFramebuffer_t besCreateAppFramebuffer(int __x, int __y, int __width, int __height);
int besInitAppFramebuffer(besAppFramebuffer_t *__handle, besAppWindow_t *__window);
void besFreeAppWindow(besAppWindow_t *__window);
int besAppWindowPollEvent(besAppWindow_t *__window);
void besAppWindowBeginFrame(besAppWindow_t *__window);
void besAppWindowEndFrame(besAppWindow_t *__window);
void besRenderPixelToAppFramebuffer(besAppFramebuffer_t *__framebuffer, int __x, int __y, besBYTE_t __r, besBYTE_t __g, besBYTE_t __b, besBYTE_t __a);
void besUpdateAppFramebuffer(besAppFramebuffer_t *__framebuffer);
void besRenderAppFramebuffer(besAppWindow_t *__window, besAppFramebuffer_t *__framebuffer);

#endif