// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

// Aulas 1-10

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Inicia a SDL e cria janela
bool init();

// Libera a midia e encerra a SDL
void close();

// Carrega as midias requisitadas
bool loadMedia();

// Carrega uma imagem individual como textura
SDL_Texture* loadTexture(std::string path);

// Janela onde vamos renderizar
SDL_Window* gWindow = NULL;

// Renderizador da janela
SDL_Renderer* gRenderer = NULL;

// constantes de cada textura para cada tecla
enum KeyPressTextures
{
    KEY_PRESS_TEXTURE_DEFAULT,
    KEY_PRESS_TEXTURE_UP,
    KEY_PRESS_TEXTURE_DOWN,
    KEY_PRESS_TEXTURE_LEFT,
    KEY_PRESS_TEXTURE_RIGHT,
    KEY_PRESS_TEXTURE_TOTAL
};

// Classe para uma textura
class LTexture
{
    private:
        // A textura em si
        SDL_Texture* mTexture;

        // Dimensoes da imagem
        int mWidth;
        int mHeight;

    public:
        LTexture();
        ~LTexture();

        // Carrega imagem
        bool loadFromFile( std::string path );

        // Desaloca textura
        void free();

        // Renderiza textura no ponto dado
        void render( int x, int y );

        // Getter das dimensoes da imagem
        int getWidth();
        int getHeight();
};

LTexture::LTexture()
{
    // Inicializa
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    // Desaloca
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    // Deleta textura preexistente
    free();

    // Textura final
    SDL_Texture* newTexture = NULL;

    // Carrega imagem
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        // Color key da imagem
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

void LTexture::render( int x, int y )
{
    // Define espaco de renderizacao e renderiza na tela
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

// Texturas da cena
LTexture gFooTexture;
LTexture gBackgroundTexture;

// Textura exibida atualmente
SDL_Texture* gTexture = NULL;

// As imagens que correspondem a cada tecla
SDL_Texture* gKeyPressTextures[ KEY_PRESS_TEXTURE_TOTAL ];

bool init() {
    bool success = true;

    // Inicia SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf("SDL not initialized! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Cria janela
        gWindow = SDL_CreateWindow("Estudo 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Window not created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Cria renderizador para a janela
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                // Inicia a cor do renderizador
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Inicia o carregamento PNG
                int imgFlags = IMG_INIT_PNG;
                if( !(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
    // Textura final
    SDL_Texture* newTexture = NULL;

    // Carrega imagem
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        // Cria textura pelos pixels da superficie
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if( newTexture == NULL)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        // Libera a surface temporaria
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool loadMedia()
{

    bool success = true;

    // Carrega carinha
    if( !gFooTexture.loadFromFile( "../resources/guy.png" ) )
    {
        printf( "Failed to load guy texture image!\n" );
        success = false;
    }
    
    // Carrega fundo
    if( !gBackgroundTexture.loadFromFile( "../resources/background.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }


    // Carrega default
    gKeyPressTextures[ KEY_PRESS_TEXTURE_DEFAULT ] = loadTexture("../resources/press.png");
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    // Carrega up
    gKeyPressTextures[ KEY_PRESS_TEXTURE_UP ] = loadTexture( "../resources/up.bmp" );
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    // Carrega down
    gKeyPressTextures[ KEY_PRESS_TEXTURE_DOWN ] = loadTexture( "../resources/down.bmp" );
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    // Carrega left
    gKeyPressTextures[ KEY_PRESS_TEXTURE_LEFT ] = loadTexture( "../resources/left.bmp" );
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    // Carrega right
    gKeyPressTextures[ KEY_PRESS_TEXTURE_RIGHT ] = loadTexture( "../resources/right.bmp" );
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

void close() {
    // Libera imagem carregada
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    gFooTexture.free();
    gBackgroundTexture.free();

    // Destroi janela
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Fecha a SDL
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] ) {

    // Inicia a SDL e cria janela
    if(!init())
    {
        printf("failed init\n");
    }
    else
    {
        // Carrega midia
        if(!loadMedia())
        {
            printf("failed to load media\n");
        }
        else
        {
            // Flag do main loop
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Seta a textura atual como a default
            // gTexture = gKeyPresssTextures[KEY_PRESS_TEXTURE_DEFAULT];

            while( !quit )
            {
                // Lida com os eventos em fila
                while(SDL_PollEvent(&e) != 0)
                {
                    // Usuario decidiu sair
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    
                    // // aula 4 (Key presses)
                    // // Usuario pressionou uma tecla
                    // else if( e.type == SDL_KEYDOWN )
                    // {
                    //     // Seleciona a textura baseada na tecla
                    //     switch( e.key.keysym.sym )
                    //     {
                    //         case SDLK_UP:
                    //         gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_UP ];
                    //         break;

                    //         case SDLK_DOWN:
                    //         gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_DOWN ];
                    //         break;

                    //         case SDLK_LEFT:
                    //         gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_LEFT ];
                    //         break;

                    //         case SDLK_RIGHT:
                    //         gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_RIGHT ];
                    //         break;

                    //         default:
                    //         gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_DEFAULT ];
                    //         // gTexture = NULL;
                    //         break;
                    //     }
                    // }
                }

                // aula 9 (The Viewport)
                // // Limpa a tela
                // SDL_RenderClear(gRenderer);

                // // Criando um viewport superior esquerdo
                // SDL_Rect topLeftViewport;
                // topLeftViewport.x = 0;
                // topLeftViewport.y = 0;
                // topLeftViewport.w = SCREEN_WIDTH / 2;
                // topLeftViewport.h = SCREEN_HEIGHT / 2;
                // SDL_RenderSetViewport( gRenderer, &topLeftViewport );

                // gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_LEFT ];
                // SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // // Criando um viewport superior direito
                // SDL_Rect topRightViewport;
                // topRightViewport.x = SCREEN_WIDTH / 2;
                // topRightViewport.y = 0;
                // topRightViewport.w = SCREEN_WIDTH / 2;
                // topRightViewport.h = SCREEN_HEIGHT / 2;
                // SDL_RenderSetViewport( gRenderer, &topRightViewport );

                // gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_RIGHT ];
                // SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // // Criando um viewport inferior
                // SDL_Rect bottomViewport;
                // bottomViewport.x = 0;
                // bottomViewport.y = SCREEN_HEIGHT / 2;
                // bottomViewport.w = SCREEN_WIDTH;
                // bottomViewport.h = SCREEN_HEIGHT / 2;
                // SDL_RenderSetViewport(gRenderer, &bottomViewport);

                // gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_DOWN ];
                // SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // aula 8 (Geometry Rendering)
                // // Renderiza um retangulo vermelho
                // SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
                // SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                // SDL_RenderFillRect(gRenderer, &fillRect);

                // // Renderiza um contorno de retangulo verde
                // SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
                // SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );        
                // SDL_RenderDrawRect( gRenderer, &outlineRect );

                //  // Renderiza linha horizontal azul
                // SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
                // SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

                // // Renderiza pontilhado amarelo vertical
                // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
                // for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
                // {
                //     SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
                // }

                // Limpa a tela
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render background texture to screen
                gBackgroundTexture.render( 0, 0 );

                //Render Foo' to the screen
                gFooTexture.render( 240, 270 );

                //Update screen
                SDL_RenderPresent( gRenderer );

                // Renderiza textura na tela
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // Atualiza a tela
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Libera recursos e fecha a SDL
    close();

    return 0;
}