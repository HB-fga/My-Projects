// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class LTexture
{
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

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};

// Timer da aplicacao
class MyTimer
{
	private:
		// Tempo no relogio de quando o timer comecou
		Uint32 mStartTicks;

		// Ticks armazenados quando o timer pausar
		Uint32 mPausedTicks;

		// status do Timer
		bool mPaused;
		bool mStarted;
	public:
		MyTimer();

		// Acoes do relogio
		void start();
		void stop();
		void pause();
		void unpause();

		Uint32 getTicks();

		// Checa o status do timer
		bool isStarted();
		bool isPaused(); 

};

class Dot
{
	private:
		// posicao X e Y do ponto
		int mPosX, mPosY;

		// velocidade do ponto
		int mVelX, mVelY;

		// caixa de colisao do ponto
		SDL_Rect mCollider;

	public:
		Dot();

		// dimensoes do ponto
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;

        // velocidade maximo de eixo do ponto
        static const int DOT_VEL = 10;
        
        // recebe input e ajusta velocidade
        void handleEvent( SDL_Event& e );

        // move o ponto
        void move(SDL_Rect& wall);

        // renderiza o ponto na tela
        void render();
};

bool init();

bool loadMedia();

void close();

bool checkCollision(SDL_Rect a, SDL_Rect b);

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;

LTexture gTimeTextTexture;
LTexture gStartPromptTextTexture;
LTexture gPausePromptTextTexture;

LTexture gDotTexture;

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

MyTimer::MyTimer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mStarted = false;
	mPaused = false;
}

void MyTimer::start()
{
	// Inicia o timer
	mStarted = true;

	// Despausa o timer
	mPaused = false;

	// Pega o tempo atual do relogio
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void MyTimer::stop()
{
	// Para o timer
	mStarted = false;

	// Despausa o timer
	mPaused = false;

	// Limpa as variaveis de ticks
	mStartTicks = 0;
	mPausedTicks = 0;
}

void MyTimer::pause()
{
	// Se o timer estiver rodando e nao estiver pausado
	if( mStarted && !mPaused)
	{
		// Pausa timer
		mPaused = true;

		// Calcula os ticks pausados
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void MyTimer::unpause()
{
	// Se o timer estiver rodando e pausado
	if(mStarted && mPaused)
	{
		// Despausa o timer
		mPaused = false;

		// Reseta os ticks iniciais
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		// Reseta os ticks pausados
		mPausedTicks = 0;
	}
}

Uint32 MyTimer::getTicks()
{
	// O tempo atual do timer
	Uint32 time = 0;

	// Se o timer estiver rodando
	if(mStarted)
	{
		// Se o timer estiver pausado
		if(mPaused)
		{
			// Retorna numero de Ticks de quando o timer foi pausado
			time = mPausedTicks;
		}
		else
		{
			// Retirn o tempo atual menos o tempo inicial
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool MyTimer::isStarted()
{
	return mStarted;
}

bool MyTimer::isPaused()
{
	return mPaused && mStarted;
}

Dot::Dot()
{
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
    mCollider.w = DOT_WIDTH;
    mCollider.h = DOT_HEIGHT;
}

void Dot::handleEvent(SDL_Event& e)
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// "acelera"
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	else if( e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// "freia"
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
		}
	}
}

void Dot::move(SDL_Rect &wall)
{
	mPosX += mVelX;
	mCollider.x = mPosX;

	mPosY += mVelY;
	mCollider.y = mPosY;

	// Previne "out of bounds"
	if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) || checkCollision( mCollider, wall ) )
    {
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }

	if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, wall ) )
    {
        mPosY -= mVelY;
		mCollider.y = mPosY;
    }
}

void Dot::render()
{
	gDotTexture.render(mPosX, mPosY);
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

	// checa se houve colisao
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
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

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			// gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
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

	gFont = TTF_OpenFont( "pixel-font.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		SDL_Color textColor = { 0, 0, 0, 255 };
		
		if( !gStartPromptTextTexture.loadFromRenderedText( "Press S to start / stop the timer.", textColor ) )
		{
			printf( "Unable to render prompt texture!\n" );
			success = false;
		}

		if( !gPausePromptTextTexture.loadFromRenderedText( "Press P to pause / unpause the timer.", textColor ) )
		{
			printf( "Unable to render prompt texture!\n" );
			success = false;
		}
	}

	if( !gDotTexture.loadFromFile("dot.bmp") )
	{
		printf( "Unable to render dot texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	gTimeTextTexture.free();
	gStartPromptTextTexture.free();
	gPausePromptTextTexture.free();

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

			Dot dot;

			SDL_Rect wall;
			wall.x = 300;
			wall.y = 40;
			wall.w = 40;
			wall.h = 400;

			SDL_Color textColor = { 0, 0, 0, 255 };

			MyTimer fpsTimer;
			MyTimer capTimer;

			int countedFrames = 0;
			fpsTimer.start();

			// Tempo a ser subtraido
			// Uint32 startTime = 0;

			// Texto que sera apresentado na tela
			std::stringstream timeText;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					// Aula 23 advanced timers
					// else if( e.type == SDL_KEYDOWN )
					// {
					// 	if(e.key.keysym.sym == SDLK_s)
					// 	{
					// 		if(timer.isStarted())
					// 		{
					// 			timer.stop();
					// 		}
					// 		else
					// 		{
					// 			timer.start();
					// 		}
					// 	}
					// 	else if(e.key.keysym.sym == SDLK_p)
					// 	{
					// 		if(timer.isPaused())
					// 		{
					// 			timer.unpause();
					// 		}
					// 		else
					// 		{
					// 			timer.pause();
					// 		}
							
					// 	}
					// }

					dot.handleEvent(e);
				}

				dot.move(wall);

				// Aula 25 capping frame rate
				// float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				// if(avgFPS > 2000000)
				// 	avgFPS = 0;

				// // Constroi string a ser apresentada
				// timeText.str( "" );
				// timeText << "Average frames per second (with cap) " << avgFPS;

				// // Transforma string em textura
				// if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				// {
				// 	printf( "Unable to render time texture!\n" );
				// }

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );        
                SDL_RenderDrawRect( gRenderer, &wall );

				dot.render();

				// Aula 25 capping frame rate
                // gTimeTextTexture.render( 120, ( SCREEN_HEIGHT - gTimeTextTexture.getHeight() ) / 2 );				

				SDL_RenderPresent( gRenderer );
				// countedFrames++;

				// // Se o frame terminou cedo
				// int frameTicks = capTimer.getTicks();
				// if(frameTicks < SCREEN_TICKS_PER_FRAME)
				// 	SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
			}
		}
	}

	close();

	return 0;
}