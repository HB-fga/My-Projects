#ifndef HTEXTURE_HPP
#define HTEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

class HTexture
{
    private:
        SDL_Texture *my_texture;

        int mWidth;
        int mHeight;

    public:
        HTexture();
        ~HTexture();

        bool loadFromFile( std::string path );
        bool loadFromRenderedText( std::string texture_text, SDL_Color text_color );

        void setBlendMode( SDL_BlendMode blending );

        void setAlpha( Uint8 alpha );

        void free();

        void render( int x, int y );

        int getWidth();
        int getHeight();
};

#endif