#include "app/bes_app.h"

void bes_appInit()
{
    logger_initConsoleLogger(NULL);
    LOG_INFO("Logger initialisation");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        LOG_ERROR("SDL Initialisation failed !");
        return;
    }
}