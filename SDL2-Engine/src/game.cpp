#include "SDL2/SDL.h"
#include "game.hpp"

#include <iostream>

SDL_Texture* player_tex;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{

    int flag = 0;

    if(fullscreen) flag = SDL_WINDOW_FULLSCREEN;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL Initialized!\n";

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
        if(window) std::cout << "Window created!\n";

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!\n";
        }

        is_running = true;

    }
    else is_running = false;

    SDL_Surface* tmp_surface = IMG_Load("assets/player.png");

}

void Game::handle_events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }

}
void Game::update()
{
    cnt++;
    std::cout << cnt << std::endl;
}
void Game::render()
{
    SDL_RenderClear(renderer);
    //add stuff to render here
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!\n";
}