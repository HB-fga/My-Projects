// #include "sdl.hpp"

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>

// #include <iostream>

// bool init()
// {
//     bool success = true;

//     if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
//     {
//         std::cout << "SDL could not initialize\n";
//         success = false;
//     }
//     else
//     {
//         if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
//         {
//             std::cout << "Linear texture filtering not enabled\n";
//         }

//         gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
//     }
    
// } 