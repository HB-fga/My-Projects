#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

class Engine
{
    private:
        SDL_Window* g_window;
        SDL_Renderer* g_renderer;
        TTF_Font *g_font;
    public:
        Engine();
        ~Engine();

        SDL_Window* get_window();
        SDL_Renderer* get_renderer();
        TTF_Font* get_font();

        void set_window(SDL_Window* g_window);
        void set_renderer(SDL_Renderer* g_renderer);
        void set_font(TTF_Font *g_font);
};

#endif