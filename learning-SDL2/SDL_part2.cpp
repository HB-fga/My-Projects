// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture
{
    private:
        // A textura em si
        SDL_Texture* mTexture;

        // dimensoes da imagem
        int mWidth;
        int mHeight;
    public:
        LTexture();
        ~LTexture();

        // Carrega imagem
        bool loadFromFile(std::string path);

        // Desaloca textura
        void free();

		// Define modulação de cores
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		// Define blending
        void setBlendMode( SDL_BlendMode blending );

        // Define modulacao alpha
        void setAlpha( Uint8 alpha );

        // Renderiza textura no ponto dado
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

        int getWidth();
        int getHeight();
    
};

// Inicia SDL
bool init();

// Carrega midia
bool loadMedia();

// Libera midia e encerra SDL
void close();

// Janela onde vamos renderizar
SDL_Window* gWindow = NULL;

// Renderizador
SDL_Renderer* gRenderer = NULL;

// Sprites da cena
SDL_Rect gSpriteClips[ 4 ];
LTexture gSpriteSheetTexture;
LTexture gModulatedTexture;
LTexture gBGFade;
LTexture gFade;

// Animacao de caminhada, SS = Sprite Sheet
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gWalkingSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gWalkingSSTexture;

// Sprite de seta
LTexture gArrowSprite;

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	// Libera textura preexistente
	free();

	// Textura final
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		// Color key
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		// Cria textura a partir da surface
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Libera surface temporario
		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    // Modula Textura
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    // Define Blending
    SDL_SetTextureBlendMode( mTexture, blending );
}
        
void LTexture::setAlpha( Uint8 alpha )
{
    // Modula alpha da textura
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	// Seta espaco de renderizacao e renderiza na tela
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	// Seta as dimensoes do corte
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Renderiza na tela
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Uhuuu!!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	// Carrega textura do sprite sheet
	if( !gSpriteSheetTexture.loadFromFile( "dots.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
	{
		// define sprite sup esquerdo
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w = 100;
		gSpriteClips[ 0 ].h = 100;

		// define sprite sup direito
		gSpriteClips[ 1 ].x = 100;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w = 100;
		gSpriteClips[ 1 ].h = 100;
		
		// define sprite inf esquerdo
		gSpriteClips[ 2 ].x =   0;
		gSpriteClips[ 2 ].y = 100;
		gSpriteClips[ 2 ].w = 100;
		gSpriteClips[ 2 ].h = 100;

		// define sprite inf direito
		gSpriteClips[ 3 ].x = 100;
		gSpriteClips[ 3 ].y = 100;
		gSpriteClips[ 3 ].w = 100;
		gSpriteClips[ 3 ].h = 100;
	}

	// Carrega textura RGB
	if( !gModulatedTexture.loadFromFile( "colors.png" ) )
	{
		printf( "Failed to load colors texture!\n" );
		success = false;
	}

	// Carrega textura Alpha Blending
	if( !gFade.loadFromFile( "fade.png" ) )
	{
		printf( "Failed to load colors texture!\n" );
		success = false;
	}
	if( !gBGFade.loadFromFile( "bg-fade.png" ) )
	{
		printf( "Failed to load colors texture!\n" );
		success = false;
	}

	// Carrega sprite sheet da caminhada
    if( !gWalkingSSTexture.loadFromFile( "walking-guy.png" ) )
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else
    {
        // Define cortes
        gWalkingSpriteClips[ 0 ].x =   0;
        gWalkingSpriteClips[ 0 ].y =   0;
        gWalkingSpriteClips[ 0 ].w =  64;
        gWalkingSpriteClips[ 0 ].h = 205;

        gWalkingSpriteClips[ 1 ].x =  64;
        gWalkingSpriteClips[ 1 ].y =   0;
        gWalkingSpriteClips[ 1 ].w =  64;
        gWalkingSpriteClips[ 1 ].h = 205;
        
        gWalkingSpriteClips[ 2 ].x = 128;
        gWalkingSpriteClips[ 2 ].y =   0;
        gWalkingSpriteClips[ 2 ].w =  64;
        gWalkingSpriteClips[ 2 ].h = 205;

        gWalkingSpriteClips[ 3 ].x = 196;
        gWalkingSpriteClips[ 3 ].y =   0;
        gWalkingSpriteClips[ 3 ].w =  64;
        gWalkingSpriteClips[ 3 ].h = 205;
    }

	if( !gArrowSprite.loadFromFile("arrow.png"))
	{
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }

	return success;
}

void close()
{
	gSpriteSheetTexture.free();
	gModulatedTexture.free();
	gBGFade.free();
	gFade.free();
	gWalkingSSTexture.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			bool quit = false;

			SDL_Event e;

			// Angulo de rotacao
			double degrees = 0;

			// Tipo de "flip"
			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			// Atual frame da animacao
			int frame = 0;

			// Componentes de modulacao
            Uint8 r = 255;
            Uint8 g = 255;
            Uint8 b = 255;

			Uint8 a = 255;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}


                    // Aula 13 alpha blending
					// else if( e.type == SDL_KEYDOWN )
                    // {
                    //     // Aumenta alpha com W
                    //     if( e.key.keysym.sym == SDLK_w )
                    //     {
                    //         // Maximo em 255
                    //         if( a + 8 > 255 )
                    //         {
                    //             a = 255;
                    //         }
                    //         else
                    //         {
                    //             a += 8;
                    //         }
                    //     }
                    //     // Diminui alpha com S
                    //     else if( e.key.keysym.sym == SDLK_s )
                    //     {
                    //         // Minimo em 0
                    //         if( a - 8 < 0 )
                    //         {
                    //             a = 0;
                    //         }
                    //         else
                    //         {
                    //             a -= 8;
                    //         }
                    //     }
                    // }


					// aula 12 color modulation
					// //  Muda os valores rgb com as teclas qwe asd
                    // else if( e.type == SDL_KEYDOWN )
                    // {
                    //     switch( e.key.keysym.sym )
                    //     {
                    //         // + vermelho
                    //         case SDLK_q:
                    //         r += 32;
                    //         break;
                            
                    //         // + verde
                    //         case SDLK_w:
                    //         g += 32;
                    //         break;
                            
                    //         // + azul
                    //         case SDLK_e:
                    //         b += 32;
                    //         break;
                            
                    //         // - vermelho
                    //         case SDLK_a:
                    //         r -= 32;
                    //         break;
                            
                    //         // - verde
                    //         case SDLK_s:
                    //         g -= 32;
                    //         break;
                            
                    //         // - azul
                    //         case SDLK_d:
                    //         b -= 32;
                    //         break;
                    //     }
                    // }

					else if(e.type == SDL_KEYDOWN)
					{
						switch(e.key.keysym.sym)
						{
							case SDLK_a:
								degrees -= 60;
								break;
                            
                            case SDLK_d:
								degrees += 60;
								break;

                            case SDLK_q:
								flipType = SDL_FLIP_HORIZONTAL;
								break;

                            case SDLK_w:
								flipType = SDL_FLIP_NONE;
								break;

                            case SDLK_e:
								flipType = SDL_FLIP_VERTICAL;
								break;
						}
					}

				}

				// Limpa tela
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				// Aula 11 Sprite Sheets
                // // Renderiza sprites
				// gSpriteSheetTexture.render( 0, 0, &gSpriteClips[ 0 ] );
				// gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );
				// gSpriteSheetTexture.render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );
				// gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );
				
				// Aula 12 color modulation
				// // Modula e renderiza textura
				// gModulatedTexture.setColor(r, g, b);
				// gModulatedTexture.render(0, 0);

				// Aula 13 alpha blending
				// // Renderiza fundo
                // gBGFade.render( 0, 0 );

                // // Renderiza frente
                // gFade.setAlpha( a );
                // gFade.render( 0, 0 );

				// Aula 14 animated sprites
				// SDL_Rect* currentClip = &gWalkingSpriteClips[frame / 4];
				// gWalkingSSTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);

				// // Seletor de frames
				// ++frame;

				// if(frame / 4 >= WALKING_ANIMATION_FRAMES)
				// 	frame = 0;

				// Aula 15 rotation and flipping
				gArrowSprite.render((SCREEN_WIDTH - gArrowSprite.getWidth()) / 2, (SCREEN_HEIGHT - gArrowSprite.getHeight()) / 2, NULL, degrees, NULL, flipType);

				// Atualiza tela
				SDL_RenderPresent( gRenderer );
				
			}
		}
	}

	close();

	return 0;
}