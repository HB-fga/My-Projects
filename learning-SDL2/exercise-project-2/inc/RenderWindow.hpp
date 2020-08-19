#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

class RenderWindow
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        RenderWindow( const char* title, int w, int h );
        SDL_Texture* loadTexture( const char* file_path );
        void cleanUp();
        void clear();
        void render( Entity& entity);
        void display();
};

#endif