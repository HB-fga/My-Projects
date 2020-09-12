#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

class Entity
{
	private:
		int mPosX, mPosY;
		int mVelX, mVelY;

        Texture entity_texture;

    public:
		Entity();
		~Entity();

		const int entity_width = 20;
		const int entity_height = 20;

		const int entity_speed = 1;

		void handleEvent( SDL_Event& e );
		void move();

		int getPosX();
		int getPosY();

        Texture get_texture();
        void set_texture(Texture texture);
};

#endif