#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity
{
    private:
        Vector2f pos;
        SDL_Rect current_frame;
        SDL_Texture* tex;

    public:
        Entity( Vector2f pos, SDL_Texture* tex );
        Vector2f& getPos();
        SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();

};

#endif