#ifndef GS_HPP
#define GS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

class GS
{
    public:

        virtual void handleEvents() = 0;
        virtual void logic() = 0;
        virtual void render() = 0;
        virtual ~GS(){};
};

#endif