#include "HTexture.hpp"
#include "globals.hpp"

HTexture::HTexture()
{
    my_texture = NULL;
    mWidth = 0;
    mHeight = 0;
}

HTexture::~HTexture()
{
    free();
}

bool HTexture::loadFromFile( std::string path )
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        
        newTexture = SDL_CreateTextureFromSurface( h_renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface( loadedSurface );
    }

    my_texture = newTexture;
    return my_texture != NULL;
}

bool HTexture::loadFromRenderedText( std::string texture_text, SDL_Color text_color )
{
	free();

	SDL_Surface *textSurface = TTF_RenderText_Solid( font, texture_text.c_str(), text_color );
	if(textSurface == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
		my_texture = SDL_CreateTextureFromSurface( h_renderer, textSurface );
		if(my_texture == NULL)
		{
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

		SDL_FreeSurface(textSurface);
	}

	return my_texture != NULL;
}

void HTexture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( my_texture, blending );
}
        
void HTexture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( my_texture, alpha );
}

void HTexture::free()
{
    if( my_texture != NULL )
    {
        SDL_DestroyTexture( my_texture );
        my_texture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void HTexture::render( int x, int y )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( h_renderer, my_texture, NULL, &renderQuad );
}

int HTexture::getWidth()
{
    return mWidth;
}

int HTexture::getHeight()
{
    return mHeight;
}