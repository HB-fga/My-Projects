// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -lSDL2_ttf -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 360;

enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    // STATE_GREEN_OVERWORLD,
    // STATE_RED_ROOM,
    // STATE_BLUE_ROOM,
    STATE_EXIT,
};

bool init();

void close();

bool loadMedia();

SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;

int alpha = 1;
int flag = 0;

class Texture
{
    private:
        SDL_Texture *my_texture;

        int mWidth;
        int mHeight;

    public:
        Texture();
        ~Texture();

        bool loadFromFile( std::string path );
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

        void setBlendMode( SDL_BlendMode blending );

        void setAlpha( Uint8 alpha );

        void free();

        void render( int x, int y );

        int getWidth();
        int getHeight();
};

class GameState
{
    public:
    virtual void handle_events() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    virtual ~GameState(){};
};

class Intro : public GameState
{
    private:
    //Intro background
    Texture background;

    //Intro message
    Texture message;

    public:
    //Loads intro resources
    Intro();
    //Frees intro resources
    ~Intro();

    //Main loop functions
    void handle_events();
    void logic();
    void render();
};

class Title : public GameState
{
    private:
    //Title screen background
    Texture background;

    //Title screen message
    Texture message;

    public:
    //Loads title screen resources
    Title();
    //Frees title resources
    ~Title();

    //Main loop functions
    void handle_events();
    void logic();
    void render();
};

/*Functions*/

//State status manager
void set_next_state( int newState );

//State changer
void change_state();

/*Globals*/

SDL_Window *window = NULL;

//The surface
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255, 0 };

//State variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

//Game state object
GameState *currentState = NULL;

Texture gBackgroundTexture;

Texture::Texture()
{
    my_texture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile( std::string path )
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

    my_texture = newTexture;
    return my_texture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if(textSurface == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
		my_texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
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

void Texture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( my_texture, blending );
}
        
void Texture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( my_texture, alpha );
}

void Texture::free()
{
    if( my_texture != NULL )
    {
        SDL_DestroyTexture( my_texture );
        my_texture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render( int x, int y )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, my_texture, NULL, &renderQuad );
}

int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}

Intro::Intro()
{
    //Load the background
    background.loadFromFile( "bg.png" );

    //Render the intro message
    gFont = TTF_OpenFont("pixel-font.ttf", 20);
    message.loadFromRenderedText( "HB studios presents...", {255, 255, 255, alpha} );
    message.setBlendMode( SDL_BLENDMODE_BLEND );
}

Intro::~Intro()
{
    background.free();
    message.free();
}

void Intro::handle_events()
{
    if(alpha == 0 && flag == 1)
        set_next_state( STATE_TITLE );

    //While there's events to handle
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        //If the user pressed enter
        else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
        {
            //Move to the title screen
            set_next_state( STATE_TITLE );
        }
    }
}

void Intro::logic()
{
    
    if(flag == 0)
    {
        alpha += 2;
        if(alpha >= 255)
        {
            flag = 1;
            alpha = 255;
        }
            
    }
    else
    {
        if(alpha > 0)
            alpha -= 2;
            if( alpha < 0)
                alpha = 0;
    }

    printf("%d\n", alpha);
    message.setAlpha( alpha );
}

void Intro::render()
{
    //Show the background
    background.render( 0, 0 );
    message.render( ( SCREEN_WIDTH - message.getWidth() ) / 2, ( SCREEN_HEIGHT - message.getHeight() ) / 2 );
    SDL_RenderPresent( gRenderer );
}

Title::Title()
{
    //Load the background
    background.loadFromFile( "tbg.png" );

    //Render the intro message
    gFont = TTF_OpenFont("pixel-font.ttf", 30);
    message.loadFromRenderedText( "Title Screen Game State!", {255, 255, 255, alpha} );

    alpha = 0;
}

Title::~Title()
{
    background.free();
    message.free();
}

void Title::handle_events()
{
    //While there's events to handle
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        //If the user pressed enter
        else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
        {
            //Go to the overworld
            set_next_state( STATE_INTRO );
        }
    }
}

void Title::logic()
{
    printf("%d\n", alpha);
}

void Title::render()
{
    background.render( 0, 0 );
    message.render( ( SCREEN_WIDTH - message.getWidth() ) / 2, ( SCREEN_HEIGHT - message.getHeight() ) / 2 );
    SDL_RenderPresent( gRenderer );
}

bool init() {
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf("SDL not initialized! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Estudo 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Window not created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if(gRenderer == NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if( !(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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

// Aula 7 (Texture Loading and Rendering)
// SDL_Surface* loadSurface( std::string path ) {

//     // Imagem final e otimizada
//     SDL_Surface* optimizedSurface = NULL;

//     // Carrega imagem
//     SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//     if(loadedSurface == NULL)
//     {
//         printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//     }
//     else
//     {
//         // Converte a superficie para o tamanho da tela
// 		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
// 		if( optimizedSurface == NULL )
// 		{
// 			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
// 		}
        
//         // Libera superficie temporaria
// 		SDL_FreeSurface( loadedSurface );
// 	}

// 	return optimizedSurface;
// }

SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if( newTexture == NULL)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool loadMedia()
{
    bool success = true;
    
    // if( !gBackgroundTexture.loadFromFile( "../resources/background.png" ) )
    // {
    //     printf( "Failed to load background texture image!\n" );
    //     success = false;
    // }

    return success;
}

void close() {
    
    gBackgroundTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

void set_next_state( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

void change_state()
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current state
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }

        //Change the state
        switch( nextState )
        {
            case STATE_INTRO:
                currentState = new Intro();
                break;

            case STATE_TITLE:
                currentState = new Title();
                break;

            // case STATE_GREEN_OVERWORLD:
            //     currentState = new OverWorld( stateID );
            //     break;

            // case STATE_RED_ROOM:
            //     currentState = new RedRoom();
            //     break;

            // case STATE_BLUE_ROOM:
            //     currentState = new BlueRoom();
            //     break;
        }

        //Change the current state ID
        stateID = nextState;

        //NULL the next state ID
        nextState = STATE_NULL;
    }
}

int main( int argc, char* args[] ) {

    if(!init())
    {
        printf("failed init\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("failed to load media\n");
        }
        else
        {
            stateID = STATE_INTRO;

            currentState = new Intro();

            int timer = 0;

            while( stateID != STATE_EXIT )
            {

                currentState->handle_events();

                currentState->logic();

                change_state();

                currentState->render();

                // while(SDL_PollEvent( &event ) != 0)
                // {
                //     if(event.type == SDL_QUIT)
                //     {
                //         quit = true;
                //     }
                    
                // }

                // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                // SDL_RenderClear( gRenderer );

                // gBackgroundTexture.render( 0, 0 );

                // SDL_RenderPresent( gRenderer );
            }
        }
    }

    close();

    return 0;
}