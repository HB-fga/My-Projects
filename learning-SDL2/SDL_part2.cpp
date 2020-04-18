// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Constantes dos botoes
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

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

		#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
		// Cria imagem a partir de string de fonte
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
		#endif

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

class LButton
{
	private:
		// posicao superior esquerda
		SDL_Point mPosition;

		// sprite global atualmente usado
		LButtonSprite mCurrentSprite;
	public:
		LButton();

		// Define posicao superior esquerda
		void setPosition(int x, int y);

		// Lida com eventos do mouse
		void handleEvent(SDL_Event* e);

		void render();
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

// Fonte global
TTF_Font *gFont = NULL;

// Sprites da cena
SDL_Rect gSpriteClips[ 4 ];
LTexture gSpriteSheetTexture;

LTexture gModulatedTexture;

LTexture gBGFade;
LTexture gFade;

LTexture gTextTexture;

LTexture gButtonSpriteSheetTexture;
SDL_Rect gButtonSpriteClips[BUTTON_SPRITE_TOTAL];

LButton gButtons[TOTAL_BUTTONS];

LTexture gPressTexture;
LTexture gUpTexture;
LTexture gDownTexture;
LTexture gLeftTexture;
LTexture gRightTexture;

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

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	free();

	//	Renderiza text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if(textSurface == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        // Cria textura a partir da surface
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if(mTexture == NULL)
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

	return mTexture != NULL;
}
#endif

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

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
	// se acontecer um evento de mouse
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if(x < mPosition.x || x > mPosition.x + BUTTON_WIDTH || y < mPosition.y || y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		// mouse fora
		if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        // mouse dentro
        else
        {
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            
                case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
                
                case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }

	}
}

void LButton::render()
{
    gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gButtonSpriteClips[ mCurrentSprite ] );
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

                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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

	// Abre a fonte
	gFont = TTF_OpenFont("font.ttf", 28);
	if(gFont == NULL)
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
	}
	else
	{
		// Renderiza texto
		SDL_Color textColor = {0, 0, 0};
		if(!gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog!", textColor))
		{
			printf( "Failed to render text texture!\n" );
            success = false;
		}
	}

	if(!gButtonSpriteSheetTexture.loadFromFile("button.png"))
	{
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else
    {
        gButtonSpriteClips[ 0 ].x = 0;
        gButtonSpriteClips[ 0 ].y = 0;
        gButtonSpriteClips[ 0 ].w = BUTTON_WIDTH;
        gButtonSpriteClips[ 0 ].h = BUTTON_HEIGHT;

        gButtonSpriteClips[ 1 ].x = 0;
        gButtonSpriteClips[ 1 ].y = BUTTON_HEIGHT;
        gButtonSpriteClips[ 1 ].w = BUTTON_WIDTH;
        gButtonSpriteClips[ 1 ].h = BUTTON_HEIGHT;
        
        gButtonSpriteClips[ 2 ].x = 0;
        gButtonSpriteClips[ 2 ].y = BUTTON_HEIGHT * 2;
        gButtonSpriteClips[ 2 ].w = BUTTON_WIDTH;
        gButtonSpriteClips[ 2 ].h = BUTTON_HEIGHT;

        gButtonSpriteClips[ 3 ].x = 0;
        gButtonSpriteClips[ 3 ].y = BUTTON_HEIGHT * 3;
        gButtonSpriteClips[ 3 ].w = BUTTON_WIDTH;
        gButtonSpriteClips[ 3 ].h = BUTTON_HEIGHT;
    }

	gButtons[ 0 ].setPosition( 0, 0 );
	gButtons[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
	gButtons[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
	gButtons[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );

	if(!gPressTexture.loadFromFile("press.png"))
	{
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
	if(!gUpTexture.loadFromFile("up.bmp"))
	{
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
	if(!gDownTexture.loadFromFile("down.bmp"))
	{
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
	if(!gLeftTexture.loadFromFile("left.bmp"))
	{
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
	if(!gRightTexture.loadFromFile("right.bmp"))
	{
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }

	return success;
}

void close()
{
	gTextTexture.free();
	gSpriteSheetTexture.free();
	gModulatedTexture.free();
	gBGFade.free();
	gFade.free();
	gWalkingSSTexture.free();
	gButtonSpriteSheetTexture.free();
	gPressTexture.free();
	gUpTexture.free();
	gDownTexture.free();
	gLeftTexture.free();
	gRightTexture.free();

	TTF_CloseFont( gFont );
	gFont = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
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

			// Textura renderizada atualmente
			LTexture* currentTexture = NULL;

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

					// aula 15 rotation and flipping
					// else if(e.type == SDL_KEYDOWN)
					// {
					// 	switch(e.key.keysym.sym)
					// 	{
					// 		case SDLK_a:
					// 			degrees -= 60;
					// 			break;
                            
                    //         case SDLK_d:
					// 			degrees += 60;
					// 			break;

                    //         case SDLK_q:
					// 			flipType = SDL_FLIP_HORIZONTAL;
					// 			break;

                    //         case SDLK_w:
					// 			flipType = SDL_FLIP_NONE;
					// 			break;

                    //         case SDLK_e:
					// 			flipType = SDL_FLIP_VERTICAL;
					// 			break;
					// 	}
					// }

					// Aula 17 Mouse Events
					// for(int i = 0;i < TOTAL_BUTTONS;i++)
					// {
					// 	gButtons[i].handleEvent(&e);
					// }

				}

				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if(currentKeyStates[SDL_SCANCODE_UP])
				{
					currentTexture = &gUpTexture;
				}
				else if(currentKeyStates[SDL_SCANCODE_DOWN])
				{
					currentTexture = &gDownTexture;
				}
				else if(currentKeyStates[SDL_SCANCODE_LEFT])
				{
					currentTexture = &gLeftTexture;
				}
				else if(currentKeyStates[SDL_SCANCODE_RIGHT])
				{
					currentTexture = &gRightTexture;
				}
				else
				{
					currentTexture = &gPressTexture;
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
				// gArrowSprite.render((SCREEN_WIDTH - gArrowSprite.getWidth()) / 2, (SCREEN_HEIGHT - gArrowSprite.getHeight()) / 2, NULL, degrees, NULL, flipType);

				// Aula 16 TTF
				// gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);

				// Aula 17 Mouse Events
				// for(int i = 0;i < TOTAL_BUTTONS;i++)
				// {
				// 	gButtons[i].render();
				// }

				currentTexture->render(0, 0);

				// Atualiza tela
				SDL_RenderPresent( gRenderer );
				
			}
		}
	}

	close();

	return 0;
}