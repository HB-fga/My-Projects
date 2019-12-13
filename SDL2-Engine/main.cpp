// //g++ -o a file.cpp `pkg-config --libs --cflags sdl2`

#include <iostream>

#include "SDL2/SDL.h"
#include "game.hpp"

Game *game = nullptr;

int main(int argc, const char * argv[]) {

    game = new Game();

    game->init("getting started", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->running()) {

        game->handle_events();
        game->update();
        game->render();

    }

    game->clean();

    return 0;
}