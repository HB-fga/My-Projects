#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
    private:
        float x, y;
        SDL_Rect current_frame;
        SDL_Texture* tex;

    public:
        Entity( float x, float y, SDL_Texture* tex );
        float getX();
        float getY();
        SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();
};

#endif