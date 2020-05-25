// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

struct Circle
{
	int x, y;
	int r;
};

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

		// colisao do ponto
		Circle mCollider;

        // move as caixas de colisao relativas ao pontog
        void shiftColliders();	
	public:

		// dimensoes do ponto
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;

        // velocidade maximo de eixo do ponto
        static const int DOT_VEL = 1;

		Dot(int x, int y);

        // recebe input e ajusta velocidade
        void handleEvent( SDL_Event& e );

        // move o ponto
        void move( SDL_Rect& square, Circle& circle );

        // renderiza o ponto na tela
        void render();

		Circle& getCollider();
};

bool init();

bool loadMedia();

void close();

// checa colisao entre circulo e circulo
bool checkCollision( Circle& a, Circle& b);

// checa colisao entre circulo e retangulo
bool checkCollision( Circle& a, SDL_Rect& b);

// calcula distancia ao quadrado
double distanceSquared( int x1, int y1, int x2, int y2);

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
			// Retorna o tempo atual menos o tempo inicial
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

void Dot::shiftColliders()
{
	int r = 0;

	// centraliza caixa de colisao
	mCollider.x = mPosX + (DOT_WIDTH - mCollider.r*2) / 2;

	// define posicao da caixa de colisao no eixo Y
	mCollider.y = mPosY + r;
	r += mCollider.r*2;
}

Dot::Dot(int x, int y)
{
	mPosX = x;
	mPosY = y;

	mCollider.r = DOT_WIDTH / 2;

	mVelX = 0;
	mVelY = 0;

	// move collider relativo ao circulo
	shiftColliders();
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

void Dot::move(SDL_Rect& square, Circle& circle)
{
	// move no eixo X
	mPosX += mVelX;
	shiftColliders();

	if( ( mPosX - mCollider.r < 0 ) || ( mPosX + mCollider.r > SCREEN_WIDTH ) || checkCollision( mCollider, square ) || checkCollision( mCollider, circle) )
    {
        mPosX -= mVelX;
		shiftColliders();
    }

	// move no eixo Y
	mPosY += mVelY;
	shiftColliders();

	if( ( mPosY - mCollider.r < 0 ) || ( mPosY + mCollider.r > SCREEN_HEIGHT ) || checkCollision( mCollider, square ) || checkCollision( mCollider, circle) )
    {
        mPosY -= mVelY;
		shiftColliders();
    }
}

void Dot::render()
{
	gDotTexture.render(mPosX - mCollider.r, mPosY - mCollider.r);
}

Circle& Dot::getCollider()
{
	return mCollider;
}

bool checkCollision(Circle& a, Circle& b)
{

	// calcula raio total ao quadrado
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	if(distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared))
	{
		// the circles collided
		return true;
	}

    return false;
}

bool checkCollision(Circle& a, SDL_Rect& b)
{

	int cX, cY;

	if( a.x < b.x)
	{
		cX = b.x;
	}
	else if( a.x > b.x + b.w)
	{
		cX = b.x + b.w;
	}
	else
	{
		cX = a.x;
	}

	if( a.y < b.y )
    {
        cY = b.y;
    }
    else if( a.y > b.y + b.h )
    {
        cY = b.y + b.h;
    }
    else
    {
        cY = a.y;
    }

	if(distanceSquared(a.x, a.y, cX, cY) < a.r * a.r)
	{
		return true;
	}

	return false;
	
}

double distanceSquared( int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;

	return deltaX*deltaX + deltaY*deltaY;
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
	gDotTexture.free();

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

			SDL_Color textColor = { 0, 0, 0, 255 };

			MyTimer fpsTimer;
			MyTimer capTimer;

			int countedFrames = 0;
			fpsTimer.start();

			// Tempo a ser subtraido
			// Uint32 startTime = 0;

			// Texto que sera apresentado na tela
			std::stringstream timeText;

			// o ponto que se movera pela tela
            Dot dot( Dot::DOT_WIDTH / 2, Dot::DOT_HEIGHT / 2 );
            Dot otherDot( SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 );

            // define a parede
            SDL_Rect wall;
            wall.x = 300;
            wall.y = 40;
            wall.w = 40;
            wall.h = 400;

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

				// move o ponto e checa colisao
                dot.move( wall, otherDot.getCollider() );

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

				// renderiza parede
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );        
                SDL_RenderDrawRect( gRenderer, &wall );

				dot.render();
				otherDot.render();

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