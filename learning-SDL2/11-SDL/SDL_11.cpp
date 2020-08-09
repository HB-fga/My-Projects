// Aula 44

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TOTAL_PARTICLES = 20;

class LTexture
{
	private:
		SDL_Texture* mTexture;
		void* mPixels;
		int mPitch;
		
		int mWidth;
		int mHeight;
		
	public:
		LTexture();

		~LTexture();
		
		bool loadFromFile( std::string path );
		
		#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		bool createBlank( int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING );

		void free();
		
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha( Uint8 alpha );
		
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		void setAsRenderTarget();
		
		int getWidth();
		int getHeight();

		// Manipuladores de pixel
		bool lockTexture();
		bool unlockTexture();
		void* getPixels();
		void copyPixels( void* pixels );
		int getPitch();
		Uint32 getPixel32( unsigned int x, unsigned int y );
};

class Particle
{
	private:
		
		int mPosX, mPosY;
		
		int mFrame;
		
		LTexture *mTexture;

	public:
		
		Particle( int x, int y );
		
		void render();

		bool isDead();
};

class Dot
{
    
    private:
		float mPosX, mPosY;
		float mVelX, mVelY;

		Particle* particles[ TOTAL_PARTICLES ];
		
		void renderParticles();

	public:
		
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		static const int DOT_VEL = 10;
		
		Dot();
		~Dot();
		
		void handleEvent( SDL_Event& e );
		
		void move( float timeStep );

		void render();
};

class LTimer
{
    public:
		LTimer();

		void start();
		void stop();
		void pause();
		void unpause();

		Uint32 getTicks();

		bool isStarted();
		bool isPaused();

    private:
		Uint32 mStartTicks;

		Uint32 mPausedTicks;

		bool mPaused;
		bool mStarted;
};

bool init();

bool loadMedia();

void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

LTexture gDotTexture;

LTexture gRedTexture;
LTexture gGreenTexture;
LTexture gBlueTexture;
LTexture gShimmerTexture;

LTexture gSplashTexture;

Uint32 callback( Uint32 interval, void* param );

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPixels = NULL;
	mPitch = 0;
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
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_GetWindowPixelFormat( gWindow ), 0 );

		if( formattedSurface == NULL )
		{
			printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
        	newTexture = SDL_CreateTexture( gRenderer, SDL_GetWindowPixelFormat( gWindow ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( newTexture == NULL )
			{
				printf("Error: Unable to create blank texture\n");
			}
			else
			{
				// trava textura para manipulacao
				SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );

				// copia pixels formatados
				memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

				// destrava textura para atualizacao
				SDL_UnlockTexture( newTexture );
				mPixels = NULL;

				// pega dimensoes da imagem
				mWidth = formattedSurface->w;
				mHeight = formattedSurface->h;
			}

			SDL_FreeSurface( formattedSurface );
		}

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::createBlank( int width, int height, SDL_TextureAccess access )
{
	// cria textura nao inicializada
	mTexture = SDL_CreateTexture( gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height );
	if( mTexture == NULL )
	{
		printf("failed!\n");
	}
	else
	{
		mWidth = width;
		mHeight = height;
	}
	
	return mTexture != NULL;
}

void LTexture::copyPixels( void* pixels )
{
	if( mPixels != NULL )
	{
		memcpy( mPixels, pixels, mPitch * mHeight );
	}
}

bool LTexture::lockTexture()
{
	bool success = true;

	if( mPixels != NULL )
	{
		printf("texture is alredy locked\n");
		success = false;
	}
	else
	{
		if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
		{
			printf("Unable to lock texture\n");
			success = false;
		}
	}

	return success;
}

bool LTexture::unlockTexture()
{
    bool success = true;

    //Texture is not locked
    if( mPixels == NULL )
    {
        printf( "Texture is not locked!\n" );
        success = false;
    }
    //Unlock texture
    else
    {
        SDL_UnlockTexture( mTexture );
        mPixels = NULL;
        mPitch = 0;
    }

    return success;
}

void* LTexture::getPixels()
{
    return mPixels;
}

int LTexture::getPitch()
{
    return mPitch;
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

void LTexture::setAsRenderTarget()
{
	SDL_SetRenderTarget( gRenderer, mTexture );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Particle::Particle( int x, int y )
{
    mPosX = x - 5 + ( rand() % 25 );
    mPosY = y - 5 + ( rand() % 25 );
    
    mFrame = rand() % 5;
    
    switch( rand() % 3 )
    {
        case 0: mTexture = &gRedTexture; break;
        case 1: mTexture = &gGreenTexture; break;
        case 2: mTexture = &gBlueTexture; break;
    }
}

void Particle::render()
{
	mTexture->render( mPosX, mPosY);
    
    if( mFrame % 2 == 0 )
    {
		gShimmerTexture.render( mPosX, mPosY );
    }

    mFrame++;
}

bool Particle::isDead()
{
    return mFrame > 10;
}

Dot::Dot()
{
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
    
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        particles[ i ] = new Particle( mPosX, mPosY );
    }
}

Dot::~Dot()
{
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        delete particles[ i ];
    }
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

void Dot::move( float timeStep )
{
	mPosX += mVelX * timeStep;
    
    if( mPosX < 0 )
    {
        mPosX = 0;
    }
	else if( mPosX > SCREEN_WIDTH - DOT_WIDTH )
	{
		mPosX = SCREEN_WIDTH - DOT_WIDTH;
	}

    mPosY += mVelY * timeStep;
    
    if( mPosY < 0 )
    {
        mPosY = 0;
    }
	else if( mPosY > SCREEN_HEIGHT - DOT_HEIGHT )
	{
		mPosY = SCREEN_HEIGHT - DOT_HEIGHT;
	}
}

void Dot::render()
{
	gDotTexture.render( (int)mPosX, (int)mPosY );

	renderParticles();
}

void Dot::renderParticles()
{
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        if( particles[ i ]->isDead() )
        {
            delete particles[ i ];
            particles[ i ] = new Particle( mPosX, mPosY );
        }
    }

    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        particles[ i ]->render();
    }
}

LTimer::LTimer()
{
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    mStarted = true;

    mPaused = false;

    mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
    mStarted = false;

    mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
    if( mStarted && !mPaused )
    {
        mPaused = true;

        mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    if( mStarted && mPaused )
    {
        mPaused = false;

        mStartTicks = SDL_GetTicks() - mPausedTicks;

        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
	Uint32 time = 0;

    if( mStarted )
    {
        if( mPaused )
        {
            time = mPausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
    return mStarted;
}

bool LTimer::isPaused()
{
    return mPaused && mStarted;
}

Uint32 callback( Uint32 interval, void* param )
{
	printf("Callback called back with message: %s\n", (char*)param );

	return 0;
}

bool init()
{
	bool success = true;
	
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
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
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if( !gSplashTexture.loadFromFile( "../resources/splash.png" ) )
	{
		printf( "Failed\n" );
		success = false;
	}
	
	if( !gDotTexture.loadFromFile( "../resources/dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	
	if( !gRedTexture.loadFromFile( "../resources/red.bmp" ) )
	{
		printf( "Failed to load red texture!\n" );
		success = false;
	}
	
	if( !gGreenTexture.loadFromFile( "../resources/green.bmp" ) )
	{
		printf( "Failed to load green texture!\n" );
		success = false;
	}

	if( !gBlueTexture.loadFromFile( "../resources/blue.bmp" ) )
	{
		printf( "Failed to load blue texture!\n" );
		success = false;
	}

	if( !gShimmerTexture.loadFromFile( "../resources/shimmer.bmp" ) )
	{
		printf( "Failed to load shimmer texture!\n" );
		success = false;
	}
	
	gRedTexture.setAlpha( 192 );
	gGreenTexture.setAlpha( 192 );
	gBlueTexture.setAlpha( 192 );
	gShimmerTexture.setAlpha( 192 );

	return success;
}

void close()
{
	gDotTexture.free();

	gRedTexture.free();
	gGreenTexture.free();
	gBlueTexture.free();
	gShimmerTexture.free();
	
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

			Dot dot;

			LTimer stepTimer;

			SDL_TimerID timerID = SDL_AddTimer( 3 * 1000, callback, (void*)"3 seconds waited!" );

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					
					dot.handleEvent( e );
				}

				float timeStep = stepTimer.getTicks() / 1000.f;

				dot.move( timeStep );

				stepTimer.start();
				
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				
				dot.render();

				gSplashTexture.render( 0, 0 );

				SDL_RenderPresent( gRenderer );
			}

			SDL_RemoveTimer( timerID );
		}

		close();

	}

	return 0;
}