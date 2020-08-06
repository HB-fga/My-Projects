// Aula 43

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

const int TOTAL_PARTICLES = 20;

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;

const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

// tile ids
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

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

class DataStream
{
	private:
		SDL_Surface* mImages[4];
		int mCurrentImage;
		int mDelayFrames;

	public:
		DataStream();

		bool loadMedia();

		void free();

		void* getBuffer();

};

class Particle
{
	private:
		
		int mPosX, mPosY;
		
		int mFrame;
		
		LTexture *mTexture;

	public:
		
		Particle( int x, int y );
		
		void render( SDL_Rect& camera );

		bool isDead();
};

class Tile
{
	private:
		SDL_Rect mBox;

		int mType;

	public:
		Tile( int x, int y, int tileType );

		void render( SDL_Rect& camera );

		int getType();

		SDL_Rect getBox();
};

class Dot
{
    
    private:
		SDL_Rect mBox;
				
		int mVelX, mVelY;

		Particle* particles[ TOTAL_PARTICLES ];
		
		void renderParticles( SDL_Rect& camera );

	public:
		
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		static const int DOT_VEL = 10;
		
		Dot();
		~Dot();
		
		void handleEvent( SDL_Event& e );
		
		void move( Tile *tiles[] );

		void setCamera( SDL_Rect& camera );

		void render(SDL_Rect& camera );
};

bool init();

bool loadMedia( Tile* tiles[] );

void close( Tile* tiles[] );

bool checkCollision( SDL_Rect a, SDL_Rect b );

bool touchesWall( SDL_Rect box, Tile* tiles[] );

bool setTiles( Tile *tiles[] );

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

LTexture gDotTexture;

LTexture gRedTexture;
LTexture gGreenTexture;
LTexture gBlueTexture;
LTexture gShimmerTexture;

LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

LTexture gFooTexture;

LTexture gStreamingTexture;

LTexture gTargetTexture;

DataStream gDataStream;

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

DataStream::DataStream()
{
	mImages[ 0 ] = NULL;
	mImages[ 1 ] = NULL;
	mImages[ 2 ] = NULL;
	mImages[ 3 ] = NULL;

	mCurrentImage = 0;
	mDelayFrames = 4;
}

bool DataStream::loadMedia()
{
	bool success = true;
	
	for( int i = 0; i < 4; ++i )
	{
		char path[ 64 ] = "";
		sprintf( path, "../resources/foo_walk_%d.png", i );

		SDL_Surface* loadedSurface = IMG_Load( path );
		if( loadedSurface == NULL )
		{
			printf( "Unable to load %s! SDL_image error: %s\n", path, IMG_GetError() );
			success = false;
		}
		else
		{
			mImages[ i ] = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0 );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return success;
}

void DataStream::free()
{
	for( int i = 0; i < 4; ++i )
	{
		SDL_FreeSurface( mImages[ i ] );
	}
}

void* DataStream::getBuffer()
{
	--mDelayFrames;
	if( mDelayFrames == 0 )
	{
		++mCurrentImage;
		mDelayFrames = 4;
	}

	if( mCurrentImage == 4 )
	{
		mCurrentImage = 0;
	}

	return mImages[ mCurrentImage ]->pixels;
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

void Particle::render( SDL_Rect& camera )
{
	mTexture->render( mPosX - camera.x, mPosY - camera.y );
    
    if( mFrame % 2 == 0 )
    {
		gShimmerTexture.render( mPosX - camera.x, mPosY - camera.y );
    }

    mFrame++;
}

bool Particle::isDead()
{
    return mFrame > 10;
}

Dot::Dot()
{
    mBox.x = 0;
    mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    mVelX = 0;
    mVelY = 0;
    
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        particles[ i ] = new Particle( mBox.x, mBox.y );
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

void Dot::move( Tile *tiles[] )
{
	mBox.x += mVelX;
    
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) )
    {
        mBox.x -= mVelX;
    }

    mBox.y += mVelY;
    
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox, tiles ) )
    {
        mBox.y -= mVelY;
    }
}

void Dot::setCamera( SDL_Rect& camera )
{
	camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

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
}

void Dot::render( SDL_Rect& camera)
{
	gDotTexture.render( mBox.x - camera.x, mBox.y - camera.y );

	renderParticles( camera );
}

void Dot::renderParticles( SDL_Rect& camera )
{
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        if( particles[ i ]->isDead() )
        {
            delete particles[ i ];
            particles[ i ] = new Particle( mBox.x, mBox.y );
        }
    }

    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        particles[ i ]->render( camera );
    }
}

Tile::Tile( int x, int y, int tileType )
{
	mBox.x = x;
	mBox.y = y;

	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	mType = tileType;
}

void Tile::render( SDL_Rect& camera )
{
	if( checkCollision( camera, mBox ) )
	{
		gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
	}
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
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

bool loadMedia( Tile* tiles[] )
{
	bool success = true;

	if( !gTargetTexture.createBlank( SCREEN_WIDTH, SCREEN_HEIGHT, SDL_TEXTUREACCESS_TARGET ) )
	{
		printf("Failed!\n");
		success = false;
	}
	
	if( !gDotTexture.loadFromFile( "../resources/dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gFooTexture.loadFromFile( "../resources/foo.png" ) )
	{
		printf( "failed\n" );
		success = false;
	}
	else
	{
		if( !gFooTexture.lockTexture() )
		{
			printf( "failed\n ");
		}
		else
		{
			// color key manual
			Uint32 format = SDL_GetWindowPixelFormat( gWindow );
			SDL_PixelFormat* mappingFormat = SDL_AllocFormat( format );

			Uint32* pixels = (Uint32*)gFooTexture.getPixels();
			int pixelCount = ( gFooTexture.getPitch() / 4 ) * gFooTexture.getHeight();

			// mapeia cores
			Uint32 colorKey = SDL_MapRGB( mappingFormat, 0, 0xFF, 0xFF );
			Uint32 transparent = SDL_MapRGBA( mappingFormat, 0xFF, 0xFF, 0xFF, 0x00 );

			for( int i = 0; i < pixelCount; ++i )
			{
				if( pixels[i] == colorKey )
				{
					pixels[i] = transparent;
				}
			}

			gFooTexture.unlockTexture();

			SDL_FreeFormat( mappingFormat );
		}
		
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

	if( !gTileTexture.loadFromFile( "../resources/tiles.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	if( !gStreamingTexture.createBlank( 64, 205 ) )
	{
		printf( "Failed to create streaming texture!\n" );
		success = false;
	}

	if( !gDataStream.loadMedia() )
	{		
		printf( "Unable to load data stream!\n" );
		success = false;
	}
	
	gRedTexture.setAlpha( 192 );
	gGreenTexture.setAlpha( 192 );
	gBlueTexture.setAlpha( 192 );
	gShimmerTexture.setAlpha( 192 );

	if( !setTiles ( tiles ) )
	{
		printf( "Failed to load tile set\n" );
		success = false;
	}

	return success;
}

void close( Tile* tiles[] )
{
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] != NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

	gDotTexture.free();

	gRedTexture.free();
	gGreenTexture.free();
	gBlueTexture.free();
	gShimmerTexture.free();

	gTileTexture.free();
	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
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

bool setTiles( Tile* tiles[] )
{
	bool tilesLoaded = true;

	int x = 0, y = 0;

	std::ifstream map( "../resources/lazy.map" );

	if( map.fail() )
	{
		printf( "Failed to load map file\n" );
		tilesLoaded = false;
	}
	else
	{
		for( int i = 0;i < TOTAL_TILES;i++)
		{
			int tileType = -1;

			map >> tileType;

			if( map.fail() )
			{
				printf( "Error loading map: Unexpected end of file!\n" );
                tilesLoaded = false;
                break;
			}

			if( ( tileType >= 0 ) && (tileType < TOTAL_TILE_SPRITES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}
			else
			{
				printf( "Error loading map: Invalid tile type at %d!\n", i );
                tilesLoaded = false;
                break;
			}

			x += TILE_WIDTH;

            if( x >= LEVEL_WIDTH )
            {
                x = 0;

                y += TILE_HEIGHT;
            }
			
		}

		if( tilesLoaded )
        {
            gTileClips[ TILE_RED ].x = 0;
            gTileClips[ TILE_RED ].y = 0;
            gTileClips[ TILE_RED ].w = TILE_WIDTH;
            gTileClips[ TILE_RED ].h = TILE_HEIGHT;

            gTileClips[ TILE_GREEN ].x = 0;
            gTileClips[ TILE_GREEN ].y = 80;
            gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
            gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

            gTileClips[ TILE_BLUE ].x = 0;
            gTileClips[ TILE_BLUE ].y = 160;
            gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
            gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

            gTileClips[ TILE_TOPLEFT ].x = 80;
            gTileClips[ TILE_TOPLEFT ].y = 0;
            gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
            gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

            gTileClips[ TILE_LEFT ].x = 80;
            gTileClips[ TILE_LEFT ].y = 80;
            gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
            gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

            gTileClips[ TILE_BOTTOMLEFT ].x = 80;
            gTileClips[ TILE_BOTTOMLEFT ].y = 160;
            gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
            gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

            gTileClips[ TILE_TOP ].x = 160;
            gTileClips[ TILE_TOP ].y = 0;
            gTileClips[ TILE_TOP ].w = TILE_WIDTH;
            gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

            gTileClips[ TILE_CENTER ].x = 160;
            gTileClips[ TILE_CENTER ].y = 80;
            gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
            gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

            gTileClips[ TILE_BOTTOM ].x = 160;
            gTileClips[ TILE_BOTTOM ].y = 160;
            gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
            gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

            gTileClips[ TILE_TOPRIGHT ].x = 240;
            gTileClips[ TILE_TOPRIGHT ].y = 0;
            gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
            gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

            gTileClips[ TILE_RIGHT ].x = 240;
            gTileClips[ TILE_RIGHT ].y = 80;
            gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
            gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

            gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
            gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
            gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
            gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
        }

	}

	map.close();

	return tilesLoaded;
	
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{

	for(int i = 0 ; i < TOTAL_TILES ; i++ )
	{
		if( (tiles[i]->getType() >= TILE_CENTER ) && ( tiles[i]->getType() <= TILE_TOPLEFT ) )
		{
			if( checkCollision( box, tiles[i]->getBox() ) )
			{
				return true;
			}
		}
	}

	return false;

}

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		Tile* tileSet[ TOTAL_TILES ];

		if( !loadMedia( tileSet ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			bool quit = false;

			SDL_Event e;

			double angle = 0;
            SDL_Point screenCenter = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

			Dot dot;

			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

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

				angle += 2;
                if( angle > 360 )
                {
                    angle -= 360;
                }

				gTargetTexture.setAsRenderTarget();
				
				dot.move( tileSet );
				dot.setCamera( camera );
				
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				
				for( int i = 0 ; i < TOTAL_TILES ; i++ )
				{
					tileSet[i]->render( camera );
				}

				dot.render( camera );

				SDL_SetRenderTarget( gRenderer, NULL );

				gTargetTexture.render( 0, 0, NULL, angle, &screenCenter );

				// gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

				gStreamingTexture.lockTexture();
                gStreamingTexture.copyPixels( gDataStream.getBuffer() );
                gStreamingTexture.unlockTexture();

				gStreamingTexture.render( (SCREEN_WIDTH - gStreamingTexture.getWidth() ) / 2, (SCREEN_HEIGHT - gStreamingTexture.getHeight() ) / 2 );

				
				SDL_RenderPresent( gRenderer );
			}
		}

		close( tileSet );

	}

	return 0;
}