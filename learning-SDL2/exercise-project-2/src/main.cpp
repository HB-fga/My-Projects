#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

#include "RenderWindow.hpp"
#include "Entity.hpp"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main( int argc, char *argv[] )
{

	if( SDL_Init( SDL_INIT_VIDEO ) > 0 )
		std::cout << "SDL_Init Failed. Error: " << SDL_GetError() << std::endl;

	if( !(IMG_Init( IMG_INIT_PNG ) ) )
		std::cout << "IMG_Init Failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window( "Game", WINDOW_WIDTH, WINDOW_HEIGHT );

	SDL_Texture* cow_texture = window.loadTexture("res/cowbg.png");

	// Entity entities[3] = { Entity( 0, 0, texture ), Entity( 30, 0, texture ), Entity( 30, 30, texture ) };

	std::vector<Entity> entities = { Entity( Vector2f( 0, 0), cow_texture ), Entity( Vector2f( 30, 0), cow_texture ), Entity( Vector2f( 0, 30), cow_texture ), Entity( Vector2f( 30, 30), cow_texture ) };

	bool quit = false;

	SDL_Event event;

	while(!quit)
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
				quit = true;
		}

		window.clear();
		
		for(Entity& e : entities)
		{
			window.render(e);
		}

		window.display();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}