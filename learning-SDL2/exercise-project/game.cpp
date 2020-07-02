// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

const int SCREEN_W = 960;
const int SCREEN_H = 540;

bool init();
bool load_media();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL could not initialize\n";
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            std::cout << "Linear texture filtering not enabled\n";
        }

        gWindow = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN );
        if(gWindow == NULL)
        {
            std::cout << "failed\n";
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                std::cout << "failed\n";
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int img_flags = IMG_INIT_PNG;
                if( !( IMG_Init( img_flags ) & img_flags) )
                {
                    std::cout << "failed\n";
                    success = false;
                }

                if( TTF_Init() == -1 )
                {
                    std::cout << "failed\n";
                    success = false;
                }

            }
            
        }
        
    }

    return success;
    
}

bool load_media()
{
    bool success = true;

    gFont = TTF_OpenFont( "pixel_font.ttf", 28 );
    if( gFont == NULL )
    {
        std::cout << "failed to load pixel-font\n";
        success = false;
    }

    return success;
}

void close()
{
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{

    if( !init() )
    {
        std::cout << "failed\n";
    }
    else
    {
        if( !load_media )
        {
            std::cout << "failed\n";
        }
        else
        {
            
            bool quit = false;

            SDL_Event e;

            while( !quit )
            {
                while( SDL_PollEvent( &e ) != 0)
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }
            }

            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            SDL_RenderPresent( gRenderer );
        }
        
    }

    close();

    return 0;
}