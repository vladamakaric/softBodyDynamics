#ifndef GLOBAL_H
#define GLOBAL_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#ifdef __linux__
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#elif defined _WIN32 || defined _WIN64
#include "SDL.h"
#include "SDL_opengl.h"
#else
#error "unknown platform"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sworld.h"

extern CSWorld* currentWorld;
extern SDL_Event event;
extern Uint8 *keystates;// = SDL_GetKeyState( NULL );

#endif
