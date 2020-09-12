// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

// I KNOW THIS CODE IS A MESS, BUT I'M STILL LEARNING

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

const int IDLE_FRAMES = 2;
const int WALK_FRAMES = 4;

bool init();

bool loadMedia();

void close();

Engine g_engine;

Texture cowbg_texture;

Texture player_idle1_texture;
Texture player_idle2_texture;

Texture player_walk1_texture;
Texture player_walk2_texture;
Texture player_walk3_texture;
Texture player_walk4_texture;

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

	if( !player_idle1_texture.loadFromFile( g_engine.get_renderer(), "res/player-idle1.png" ) )
	{
		printf( "Failed to load player idle 1 texture!\n" );
		success = false;
	}
	if( !player_idle2_texture.loadFromFile( g_engine.get_renderer(), "res/player-idle2.png" ) )
	{
		printf( "Failed to load player idle 2 texture!\n" );
		success = false;
	}

	if( !player_walk1_texture.loadFromFile( g_engine.get_renderer(), "res/player-walk1.png" ) )
	{
		printf( "Failed to load player walk 1 texture!\n" );
		success = false;
	}
	if( !player_walk2_texture.loadFromFile( g_engine.get_renderer(), "res/player-walk2.png" ) )
	{
		printf( "Failed to load player walk 2 texture!\n" );
		success = false;
	}
	if( !player_walk3_texture.loadFromFile( g_engine.get_renderer(), "res/player-walk3.png" ) )
	{
		printf( "Failed to load player walk 3 texture!\n" );
		success = false;
	}
	if( !player_walk4_texture.loadFromFile( g_engine.get_renderer(), "res/player-walk4.png" ) )
	{
		printf( "Failed to load player walk 4 texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	player_idle1_texture.free();
	player_idle2_texture.free();

	player_walk1_texture.free();
	player_walk2_texture.free();
	player_walk3_texture.free();
	player_walk4_texture.free();
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

			player.get_texture().loadFromFile( g_engine.get_renderer(), "res/player-idle1.png" );

            // FOR SOME REASON IT ERASES THE TEXTURE
            // player.set_texture(player_texture);

			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			int current_scene = 0;

			int scrolling_offset = 0;
			int scrolling_up = 1;

			int player_lastx = 0;
			int player_lasty = 0;

			int player_animation_type = 0;

			int walk_frame = 0;
			int idle_frame = 0;

			SDL_RendererFlip flip_type = SDL_FLIP_NONE;

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

						if(player_lastx > player.getPosX())
						{
							flip_type = SDL_FLIP_HORIZONTAL;
							player_animation_type = 1;
							idle_frame = 0;
						}
						else if(player_lastx < player.getPosX())
						{
							flip_type = SDL_FLIP_NONE;
							player_animation_type = 1;
							idle_frame = 0;
						}

						if(player_lasty != player.getPosY())
						{
							player_animation_type = 1;
							idle_frame = 0;
						}

						if( player_lastx == player.getPosX() && player_lasty == player.getPosY() )
						{
							player_animation_type = 0;
							walk_frame = 0;
						}

						player_lastx = player.getPosX();
						player_lasty = player.getPosY();

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

						cowbg_texture.render( g_engine.get_renderer(), 0, 0, &camera);

						switch (player_animation_type)
						{
							case 0:
								if (idle_frame < 60)
								{
									player_idle1_texture.render(g_engine.get_renderer(), player.getPosX() - camera.x, player.getPosY()-camera.y, NULL, 0.0, NULL, flip_type);
									idle_frame++;
								}
								else if ( idle_frame < 120 )
								{
									player_idle2_texture.render(g_engine.get_renderer(), player.getPosX() - camera.x, player.getPosY()-camera.y, NULL, 0.0, NULL, flip_type);
									idle_frame++;

									if(idle_frame == 120) idle_frame = 0;
								}
								
								break;

							case 1:
								if (walk_frame < 10)
								{
									player_walk1_texture.render(g_engine.get_renderer(), player.getPosX() - camera.x, player.getPosY()-camera.y, NULL, 0.0, NULL, flip_type);
									walk_frame++;
								}
								else if (walk_frame < 20)
								{
									player_walk2_texture.render(g_engine.get_renderer(), player.getPosX() - camera.x, player.getPosY()-camera.y, NULL, 0.0, NULL, flip_type);
									walk_frame++;
								}
								else if (walk_frame < 30)
								{
									player_walk3_texture.render(g_engine.get_renderer(), player.getPosX() - camera.x, player.getPosY()-camera.y, NULL, 0.0, NULL, flip_type);
									walk_frame++;
								}
								else if ( walk_frame < 40 )
								{
									player_walk4_texture.render(g_engine.get_renderer(), player.getPosX() - camera.x, player.getPosY()-camera.y, NULL, 0.0, NULL, flip_type);
									walk_frame++;

									if(walk_frame == 40) walk_frame = 0;
								}
								break;
						}

						break;
				}

				SDL_RenderPresent( g_engine.get_renderer() );
			}
		}
	}

	close();

	return 0;
}