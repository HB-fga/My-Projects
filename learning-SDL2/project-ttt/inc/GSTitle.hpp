#ifndef GSTITLE_HPP
#define GSTITLE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

#include "GS.hpp"
#include "HTexture.hpp"

class GSTitle : public GS
{
    private:
        HTexture background;
        HTexture message;

    public:
        GSTitle();
        ~GSTitle();

        void handleEvents();
        void logic();
        void render();
};

#endif