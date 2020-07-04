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

Texture gDotTexture;
Texture gBGTexture;

Texture gPromptTextTexture;
Texture gInputTextTexture;

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

		g_engine.set_window(SDL_CreateWindow( "Estudo 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ));
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

	g_engine.set_font(TTF_OpenFont( "pixel-font.ttf", 28 ));
	if( g_engine.get_font() == NULL )
	{
		printf( "Failed to load pixel font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		SDL_Color textColor = { 0, 0, 0, 0xFF };
		if( !gPromptTextTexture.loadFromRenderedText( g_engine.get_renderer(), g_engine.get_font(), "Prompt Text", textColor ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
	}

	if( !gDotTexture.loadFromFile( g_engine.get_renderer(), "dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gBGTexture.loadFromFile( g_engine.get_renderer(), "bg1.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	gDotTexture.free();
	gBGTexture.free();

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

			Entity dot;

            // FOR SOME REASON IT ERASES THE TEXTURE
            // dot.set_texture(gDotTexture);

			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			while( !quit )
			{

				bool renderText = false;

				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					dot.handleEvent( e );
				}

				dot.move();

				// camera.x = ( dot.getPosX() + Entity::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
				// camera.y = ( dot.getPosY() + Entity::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

                camera.x = ( dot.getPosX() + 20 / 2 ) - SCREEN_WIDTH / 2;
				camera.y = ( dot.getPosY() + 20 / 2 ) - SCREEN_HEIGHT / 2;

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

				SDL_SetRenderDrawColor( g_engine.get_renderer(), 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( g_engine.get_renderer() );

				gBGTexture.render( g_engine.get_renderer(), 0, 0, &camera );

				gPromptTextTexture.render( g_engine.get_renderer(), ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0 );

				// dot.get_texture().render( g_engine.get_renderer(), dot.getPosX() - camera.x, dot.getPosY() - camera.y );
                gDotTexture.render(g_engine.get_renderer(), dot.getPosX() - camera.x, dot.getPosY()-camera.y);

				SDL_RenderPresent( g_engine.get_renderer() );
			}
		}
	}

	close();

	return 0;
}