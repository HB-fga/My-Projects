// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include "engine.hpp"
#include "texture.hpp"
#include "entity.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

bool init();

bool loadMedia();

void close();

Engine g_engine;

Texture player_texture;
Texture cowbg_texture;

Texture prompt_text_texture;
Texture title_text_texture;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		g_engine.set_window(SDL_CreateWindow( "Cow Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ));
		if( g_engine.get_window() == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			g_engine.set_renderer(SDL_CreateRenderer( g_engine.get_window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ));
			if( g_engine.get_renderer() == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( g_engine.get_renderer(), 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	g_engine.set_font(TTF_OpenFont( "res/pixel-font.ttf", 70 ));
	if( g_engine.get_font() == NULL )
	{
		printf( "Failed to load pixel font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		SDL_Color textColor = { 0xFF, 0xA5, 0x00, 0xFF };
		if( !title_text_texture.loadFromRenderedText( g_engine.get_renderer(), g_engine.get_font(), "COW GAME!", textColor ) )
		{
			printf( "Failed to render title text!\n" );
			success = false;
		}
	}

	g_engine.set_font(TTF_OpenFont( "res/pixel-font.ttf", 28 ));
	if( g_engine.get_font() == NULL )
	{
		printf( "Failed to load pixel font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		SDL_Color textColor = { 0, 0, 0, 0xFF };
		if( !prompt_text_texture.loadFromRenderedText( g_engine.get_renderer(), g_engine.get_font(), "Prompt Text", textColor ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
	}

	if( !cowbg_texture.loadFromFile( g_engine.get_renderer(), "res/cowbg.png" ) )
	{
		printf( "Failed to load cow background texture!\n" );
		success = false;
	}

	if( !player_texture.loadFromFile( g_engine.get_renderer(), "res/player-idle1.png" ) )
	{
		printf( "Failed to load player idle 1 texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	player_texture.free();
	cowbg_texture.free();

	SDL_DestroyRenderer( g_engine.get_renderer() );
	SDL_DestroyWindow( g_engine.get_window() );
	g_engine.set_renderer(NULL);
    g_engine.set_window(NULL);

	IMG_Quit();
    TTF_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			Entity player;

            // FOR SOME REASON IT ERASES THE TEXTURE
            // dot.set_texture(gDotTexture);

			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			int current_scene = 0;

			int scrolling_offset = 0;
			int scrolling_up = 1;

			while( !quit )
			{

				bool renderText = false;

				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN)
					{
						switch( current_scene )
						{
							case 0:
								if( e.key.keysym.sym == SDLK_RETURN ) current_scene = 1;

								break;
							case 1:

								break;
						}
					}

					player.handleEvent( e );
				}

				SDL_SetRenderDrawColor( g_engine.get_renderer(), 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( g_engine.get_renderer() );

				switch( current_scene )
				{
					case 0:
						scrolling_offset--;
						if( scrolling_offset < -cowbg_texture.getWidth() / 3 ) 
						{
							scrolling_offset = 0;
							scrolling_up = scrolling_up * (-1);
						} 

						cowbg_texture.render( g_engine.get_renderer(), scrolling_offset, -cowbg_texture.getHeight() / 3 + (scrolling_offset * scrolling_up) );

						title_text_texture.render( g_engine.get_renderer(), ( SCREEN_WIDTH - title_text_texture.getWidth() ) / 2, (SCREEN_HEIGHT - title_text_texture.getHeight() ) / 2 );

						break;
					case 1:
						player.move();

						camera.x = ( player.getPosX() + 20 / 2 ) - SCREEN_WIDTH / 2;
						camera.y = ( player.getPosY() + 20 / 2 ) - SCREEN_HEIGHT / 2;

						if( camera.x < 0 )
						{ 
							camera.x = 0; 
						}
						if( camera.y < 0 )
						{
							camera.y = 0;
						}
						if( camera.x > LEVEL_WIDTH - camera.w )
						{
							camera.x = LEVEL_WIDTH - camera.w;
						}
						if( camera.y > LEVEL_HEIGHT - camera.h )
						{
							camera.y = LEVEL_HEIGHT - camera.h;
						}


						prompt_text_texture.render( g_engine.get_renderer(), ( SCREEN_WIDTH - prompt_text_texture.getWidth() ) / 2, 0 );

						player_texture.render(g_engine.get_renderer(), player.getPosX() - camera.x, player.getPosY()-camera.y);

						break;
				}

				SDL_RenderPresent( g_engine.get_renderer() );
			}
		}
	}

	close();

	return 0;
}