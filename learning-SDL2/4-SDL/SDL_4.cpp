// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

// Aulas 30-?

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

// Tamanho do cenario
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

// Tamanho da camera/tela
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TOTAL_DATA = 10;

class LWindow
{
    private:
        SDL_Window* mWindow;

        int mWidth;
        int mHeight;

        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized;
	public:
        LWindow();

        bool init();

        SDL_Renderer* createRenderer();

        void handleEvent( SDL_Event& e );

        void free();

        int getWidth();
        int getHeight();

        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool isMinimized();
};

class LTexture
{
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;

	public:
		LTexture();
		~LTexture();

		bool loadFromFile( std::string path );
		
		#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getWidth();
		int getHeight();

	
};

class Dot
{
	private:
		int mPosX, mPosY;
		int mVelX, mVelY;

    public:
		Dot();

		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		static const int DOT_VEL = 10;

		void handleEvent( SDL_Event& e );
		void move();

		// Recebe a posicao da camera para renderizar apenas o espaco relativo a posicao do ponto
		void render( int camX, int camY );

		int getPosX();
		int getPosY();
};

bool init();

bool loadMedia();

void close();

LWindow gWindow;

SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;

LTexture gDotTexture;
LTexture gBGTexture;

LTexture gPromptTextTexture;
LTexture gInputTextTexture;

LTexture gDataTextures[ TOTAL_DATA ];

Sint32 gData[ TOTAL_DATA ];

LWindow::LWindow()
{
    mWindow = NULL;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mMinimized = false;
    mWidth = 0;
    mHeight = 0;
}

bool LWindow::init()
{
	// cria janela
    mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if( mWindow != NULL )
    {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;
    }

    return mWindow != NULL;
}

SDL_Renderer* LWindow::createRenderer()
{
    return SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

void LWindow::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_WINDOWEVENT )
    {
        bool updateCaption = false;
		switch( e.window.event )
        {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
				mWidth = e.window.data1;
				mHeight = e.window.data2;
				SDL_RenderPresent( gRenderer );
				break;

            case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent( gRenderer );
				break;

            case SDL_WINDOWEVENT_ENTER:
				mMouseFocus = true;
				updateCaption = true;
				break;
            
            case SDL_WINDOWEVENT_LEAVE:
				mMouseFocus = false;
				updateCaption = true;
				break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
				mKeyboardFocus = true;
				updateCaption = true;
				break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
				mKeyboardFocus = false;
				updateCaption = true;
				break;

            case SDL_WINDOWEVENT_MINIMIZED:
				mMinimized = true;
				break;

            case SDL_WINDOWEVENT_MAXIMIZED:
				mMinimized = false;
				break;
            
            case SDL_WINDOWEVENT_RESTORED:
				mMinimized = false;
				break;
        }
        if( updateCaption )
        {
            std::stringstream caption;
            caption << "Estudo 4 - Foco do Mouse:" << ( ( mMouseFocus ) ? "Sim" : "Nao" ) << " Foco do Teclado:" << ( ( mKeyboardFocus ) ? "Sim" : "Nao" );
            SDL_SetWindowTitle( mWindow, caption.str().c_str() );
        }
    }
    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
    {
        if( mFullScreen )
        {
            SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
            mFullScreen = false;
        }
        else
        {
            SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
            mFullScreen = true;
            mMinimized = false;
        }
    }
}

void LWindow::free()
{
	if( mWindow != NULL )
	{
		SDL_DestroyWindow( mWindow );
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int LWindow::getWidth()
{
    return mWidth;
}

int LWindow::getHeight()
{
    return mHeight;
}

bool LWindow::hasMouseFocus()
{
    return mMouseFocus;
}

bool LWindow::hasKeyboardFocus()
{
    return mKeyboardFocus;
}

bool LWindow::isMinimized()
{
    return mMinimized;
}

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

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
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
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Dot::Dot()
{
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move()
{
    mPosX += mVelX;

    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > LEVEL_WIDTH ) )
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > LEVEL_HEIGHT ) )
    {
        mPosY -= mVelY;
    }
}

void Dot::render( int camX, int camY )
{
	// Renderiza apenas a parte observada pela camera
	gDotTexture.render( mPosX - camX, mPosY - camY );
}

int Dot::getPosX()
{
	return mPosX;
}

int Dot::getPosY()
{
	return mPosY;
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

		if( !gWindow.init() )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = gWindow.createRenderer();
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
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				#endif
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	SDL_Color textColor = { 0, 0, 0, 0xFF };
	SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

	SDL_RWops* file = SDL_RWFromFile( "nums.bin", "r+b" );

	if( file == NULL )
	{
		printf( "Warning: Unable to open file!\n" );

		file = SDL_RWFromFile( "nums.bin", "w+b" );
		if( file != NULL )
		{
			printf( "New file created!\n" );

			for(int i = 0; i < TOTAL_DATA; i++)
			{
				gData[i] = 0;
				SDL_RWwrite(file, &gData[i], sizeof(Sint32), 1 );
			}

			SDL_RWclose( file );

		}
		else
		{
			printf( "Error: Unable to create file!\n" );
			success = false;
		}
		
	}
	else
	{
		printf( "Reading file...!\n" );
		for(int i = 0;i < TOTAL_DATA;i++)
		{
			SDL_RWread( file, &gData[i], sizeof(Sint32), 1 );
		}

		SDL_RWclose( file );
	}
	

	gFont = TTF_OpenFont( "pixel-font.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load pixel font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		SDL_Color textColor = { 0, 0, 0, 0xFF };
		if( !gPromptTextTexture.loadFromRenderedText( "Enter Text:", textColor ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
	}

	gDataTextures[ 0 ].loadFromRenderedText( std::to_string( gData[ 0 ] ), highlightColor );
    for( int i = 1; i < TOTAL_DATA; ++i )
    {
        gDataTextures[ i ].loadFromRenderedText( std::to_string( gData[ i ] ), textColor );
    }

	if( !gDotTexture.loadFromFile( "dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	// if( !gBGTexture.loadFromFile( "bg1.png" ) )
	// {
	// 	printf( "Failed to load background texture!\n" );
	// 	success = false;
	// }

	if( !gBGTexture.loadFromFile( "bg2.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	// "saving progress"
	SDL_RWops* file = SDL_RWFromFile( "nums.bin", "w+b" );
	if( file != NULL )
	{
		for(int i = 0;i < TOTAL_DATA;i++)
		{
			SDL_RWwrite( file, &gData[i], sizeof(Sint32), 1 );
		}

		SDL_RWclose( file );
	}
	else
	{
		printf( "Error: Unable to save file\n" );
	}

	gDotTexture.free();
	gBGTexture.free();

	SDL_DestroyRenderer( gRenderer );
	gWindow.free();

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

			Dot dot;

			// Cor do texto
            SDL_Color textColor = { 0, 0, 0, 0xFF };
            SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

			// Deslocamento do background animado
			int scrollingOffset = 0;

			// // Area da camera 
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			// Texto atual
			std::string inputText = "Some Text";
			gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );

            // Input atual
            int currentData = 0;

			// Habilita entrada de texto
			SDL_StartTextInput();

			while( !quit )
			{

				bool renderText = false;

				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
								gDataTextures[ currentData ].loadFromRenderedText( std::to_string( gData[ currentData ] ), textColor );
								
								--currentData;
								if( currentData < 0 )
								{
									currentData = TOTAL_DATA -1;
								}

								gDataTextures[ currentData ].loadFromRenderedText( std::to_string( gData[ currentData ] ), highlightColor );

								break;

							case SDLK_DOWN:
								gDataTextures[ currentData ].loadFromRenderedText( std::to_string( gData[ currentData ] ), textColor );
								
								++currentData;
								if( currentData == TOTAL_DATA )
								{
									currentData = TOTAL_DATA -1;
								}

								gDataTextures[ currentData ].loadFromRenderedText( std::to_string( gData[ currentData ] ), highlightColor );

								break;

							case SDLK_LEFT:
								--gData[ currentData ];
								gDataTextures[ currentData ].loadFromRenderedText( std::to_string( gData[ currentData ] ), highlightColor );

                            break;
                            
                            case SDLK_RIGHT:
								++gData[ currentData ];
								gDataTextures[ currentData ].loadFromRenderedText( std::to_string( gData[ currentData ] ), highlightColor );

                            break;
						}
					}

					// // Aula 32 Input de texto e area de transferencia
					// // Definindo algumas acoes especiais (Backspace , ctrl c , ctrl v)
					// else if( e.type == SDL_KEYDOWN)
					// {
					// 	if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
					// 	{
					// 		inputText.pop_back();
					// 		renderText = true;
					// 	}
					// 	else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
					// 	{
					// 		SDL_SetClipboardText( inputText.c_str() );
					// 	}
					// 	else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
					// 	{
					// 		inputText += SDL_GetClipboardText();
					// 		renderText = true;
					// 	}
					// }
					// else if( e.type == SDL_TEXTINPUT )
                    // {
                    //     if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )
                    //     {
                    //         inputText += e.text.text;
                    //         renderText = true;
                    //     }
                    // }

					gWindow.handleEvent( e );
					dot.handleEvent( e );
				}

				dot.move();

				// Rola background
				--scrollingOffset;
				if(scrollingOffset < -gBGTexture.getWidth()) scrollingOffset = 0;

				// // Define a posicao da camera
				camera.x = ( dot.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
				camera.y = ( dot.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

				// Mantem a camera dentro dos limites do cenario
				if( camera.x < 0 )
				{ 
					camera.x = 0;
				}
				if( camera.y < 0 )
				{
					camera.y = 0;
				}
				if( camera.x > LEVEL_WIDTH - camera.w )
				{
					camera.x = LEVEL_WIDTH - camera.w;
				}
				if( camera.y > LEVEL_HEIGHT - camera.h )
				{
					camera.y = LEVEL_HEIGHT - camera.h;
				}

				if( !gWindow.isMinimized() )
				{
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );

					// gBGTexture.render( 0, 0, &camera );
					gBGTexture.render( scrollingOffset, 0 );
					gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

					if( renderText )
					{
						if(inputText != "")
						{
							gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
						}
						else
						{
							gInputTextTexture.loadFromRenderedText( " ", textColor );
						}
						
					}

					gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0 );
					gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, gPromptTextTexture.getHeight() );

					for(int i = 0;i < TOTAL_DATA;i++)
					{
						gDataTextures[i].render( ( SCREEN_WIDTH - gDataTextures[i].getWidth() ) / 2, gPromptTextTexture.getHeight() * 2 + gDataTextures[ 0 ].getHeight() * i );
					}

					dot.render( camera.x, camera.y );

					SDL_RenderPresent( gRenderer );
				}
			}

			// Desabilita entrada de texto
			SDL_StopTextInput();
		}
	}

	close();

	return 0;
}