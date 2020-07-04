#include "engine.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

Engine::Engine()
{
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
}

Engine::~Engine()
{

}

SDL_Renderer* Engine::get_renderer()
{
    return this->g_renderer;
}

SDL_Window* Engine::get_window()
{
    return this->g_window;
}

TTF_Font* Engine::get_font()
{
    return this->g_font;
}

void Engine::set_window(SDL_Window* g_window)
{
    this->g_window = g_window;
}

void Engine::set_renderer(SDL_Renderer* g_renderer)
{
    this->g_renderer = g_renderer;
}

void Engine::set_font(TTF_Font *g_font)
{
    this->g_font = g_font;
}