#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

#include "GS.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 360;

enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    STATE_PVP,
    STATE_EXIT,
};

extern SDL_Window *h_window;
extern SDL_Renderer *h_renderer;
extern SDL_Event event;

extern TTF_Font *font;
extern SDL_Color text_color;

extern int state_ID;
extern int next_state;

extern GS *current_state;

#endif
