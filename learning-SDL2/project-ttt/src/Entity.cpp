#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity( float x, float y, SDL_Texture* tex)
:x(x), y(y), tex(tex)
{
    current_frame.x = 0;
    current_frame.y = 0;
    current_frame.w = 32;
    current_frame.h = 32;
}

float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}

SDL_Texture* Entity::getTex()
{
    return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
    return current_frame;
}