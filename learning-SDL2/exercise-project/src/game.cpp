// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

#include "constants.hpp"
#include "sdl.hpp"

int main( int argc, char* args[] )
{

    if( !init() )
    {
        std::cout << "failed\n";
    }
    else
    {
        if( !load_media() )
        {
            std::cout << "failed\n";
        }
        else
        {
            main_code();
        }
        
    }

    close();

    return 0;
}