#include "texture.hpp"
#include "entity.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

Entity::Entity()
{
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
}

Entity::~Entity()
{

}

void Entity::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= entity_speed; break;
            case SDLK_DOWN: mVelY += entity_speed; break;
            case SDLK_LEFT: mVelX -= entity_speed; break;
            case SDLK_RIGHT: mVelX += entity_speed; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += entity_speed; break;
            case SDLK_DOWN: mVelY -= entity_speed; break;
            case SDLK_LEFT: mVelX += entity_speed; break;
            case SDLK_RIGHT: mVelX -= entity_speed; break;
        }
    }
}

void Entity::move()
{
    mPosX += mVelX;

    if( ( mPosX < 0 ) || ( mPosX + 20 > 1280 ) )
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if( ( mPosY < 0 ) || ( mPosY + 20 > 960 ) )
    {
        mPosY -= mVelY;
    }
}

int Entity::getPosX()
{
	return this->mPosX;
}

int Entity::getPosY()
{
	return this->mPosY;
}

Texture Entity::get_texture()
{
    return this->entity_texture;
}

void Entity::set_texture(Texture texture)
{
    this->entity_texture = texture;
}