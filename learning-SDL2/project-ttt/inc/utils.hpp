#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

bool init();
void close();

void set_next_state( int new_state );
void change_state();

#endif
