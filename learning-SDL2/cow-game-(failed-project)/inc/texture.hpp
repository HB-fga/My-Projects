#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

class Texture
{
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;

	public:
		Texture();
		~Texture();

		bool loadFromFile( SDL_Renderer* g_renderer, std::string path );
		
		bool loadFromRenderedText( SDL_Renderer* g_renderer, TTF_Font *g_font, std::string textureText, SDL_Color textColor );

		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		void render( SDL_Renderer* g_renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getWidth();
		int getHeight();	
};

#endif