#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity( Vector2f pos, SDL_Texture* tex )
:pos(pos), tex(tex)
{
    current_frame.x = 0;
    current_frame.y = 0;
    current_frame.w = 32;
    current_frame.h = 32;
}

Vector2f& Entity::getPos()
{
    return pos;
}

SDL_Texture* Entity::getTex()
{
    return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
    return current_frame;
}