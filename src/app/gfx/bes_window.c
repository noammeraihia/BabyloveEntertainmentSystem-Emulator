#include "app/gfx/bes_window.h"

besAppWindow_t besCreateAppWindow(const char *__name, int __width, int __height, SDL_WindowFlags __wF, SDL_RendererFlags __rF, besAppFramebuffer_t __coreOutput)
{
    besAppWindow_t _handle = {
        .width = __width,
        .height = __height,
        .coreOutput = __coreOutput,
        .isCOShown = true,

        .handle = NULL,
        .renderer = NULL};

    _handle.handle = SDL_CreateWindow(__name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, __width, __height, __wF);
    if (!_handle.handle)
    {
        LOG_ERROR("%s", SDL_GetError());
        return (besAppWindow_t){0};
    }

    _handle.renderer = SDL_CreateRenderer(_handle.handle, -1, __rF);
    if (!_handle.renderer)
    {
        LOG_ERROR("%s", SDL_GetError());
        return (besAppWindow_t){0};
    }

    besInitAppFramebuffer(&_handle.coreOutput, &_handle);

    return _handle;
}

besAppFramebuffer_t besCreateAppFramebuffer(int __x, int __y, int __width, int __height)
{
    return (besAppFramebuffer_t){
        .x = __x,
        .y = __y,
        .width = __width,
        .height = __height,
        .destRect = {
            .x = __x,
            .y = __y,
            .w = __width,
            .h = __height},
        .handle = NULL,
        .pixelsData = NULL};
}

int besInitAppFramebuffer(besAppFramebuffer_t *__handle, besAppWindow_t *__window)
{
    __handle->handle = SDL_CreateTexture(__window->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, __handle->width, __handle->height);
    if (!__handle->handle)
    {
        LOG_ERROR("%s", SDL_GetError());
        return -1;
    }

    __handle->pixelsData = (besDWORD_t *)malloc(sizeof(besDWORD_t) * __handle->width * __handle->height);
    if (!__handle->pixelsData)
    {
        LOG_ERROR("Dynamic HEAP ALLOC failed !");
        return -1;
    }

    memset(__handle->pixelsData, 25, __handle->width * __handle->height * sizeof(besDWORD_t));

    return 0;
}

void besFreeAppWindow(besAppWindow_t *__window)
{
    free(__window->coreOutput.pixelsData);
    SDL_DestroyTexture(__window->coreOutput.handle);
    SDL_DestroyRenderer(__window->renderer);
    SDL_DestroyWindow(__window->handle);
}

int besAppWindowPollEvent(besAppWindow_t *__window)
{
    return SDL_PollEvent(&__window->event);
}

void besAppWindowBeginFrame(besAppWindow_t *__window)
{
    SDL_SetRenderDrawColor(__window->renderer, 0, 0, 25, 255);
    SDL_RenderClear(__window->renderer);
}

void besAppWindowEndFrame(besAppWindow_t *__window)
{
    besUpdateAppFramebuffer(&__window->coreOutput);
    besRenderAppFramebuffer(__window, &__window->coreOutput);
    SDL_RenderPresent(__window->renderer);
}

void besRenderPixelToAppFramebuffer(besAppFramebuffer_t *__framebuffer, int __x, int __y, besBYTE_t __r, besBYTE_t __g, besBYTE_t __b, besBYTE_t __a)
{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    __framebuffer->pixelsData[__x + (__y * __framebuffer->width)] = (__a << 8 * 3) | (__b << 8 * 0) | (__g << 8 * 1) | (__r << 8 * 2);
#else
    __framebuffer->pixelsData[__x + (__y * __framebuffer->width)] = (__b << 8 * 3) | (__g << 8 * 2) | (__r << 8 * 1) | (__a << 8 * 0);
#endif
}

void besUpdateAppFramebuffer(besAppFramebuffer_t *__framebuffer)
{
    SDL_UpdateTexture(__framebuffer->handle, NULL, __framebuffer->pixelsData, __framebuffer->width * sizeof(besDWORD_t));
}

void besRenderAppFramebuffer(besAppWindow_t *__window, besAppFramebuffer_t *__framebuffer)
{
    if (__window->isCOShown)
    {
        SDL_RenderClear(__window->renderer);
        SDL_RenderCopy(__window->renderer, __framebuffer->handle, NULL, &__framebuffer->destRect);
    }
}

void besAppWindowRenderText(besAppWindow_t *__window, const char *__text, SDL_Color __color)
{
}