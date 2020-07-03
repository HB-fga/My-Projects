#ifndef SDL_HPP
#define SDL_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "sdl.hpp"

bool init();
bool load_media();
void close();
bool main_code();

#endif