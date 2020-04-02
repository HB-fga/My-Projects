// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
        gWindow = SDL_CreateWindow("Yaaaay!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
                // Inicia a core do renderizador
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

    // Carrega default
    gKeyPressTextures[ KEY_PRESS_TEXTURE_DEFAULT ] = loadTexture("press.png");
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    // Carrega up
    gKeyPressTextures[ KEY_PRESS_TEXTURE_UP ] = loadTexture( "up.bmp" );
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    // Carrega down
    gKeyPressTextures[ KEY_PRESS_TEXTURE_DOWN ] = loadTexture( "down.bmp" );
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    // Carrega left
    gKeyPressTextures[ KEY_PRESS_TEXTURE_LEFT ] = loadTexture( "left.bmp" );
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    // Carrega right
    gKeyPressTextures[ KEY_PRESS_TEXTURE_RIGHT ] = loadTexture( "right.bmp" );
    if( gKeyPressTextures[ KEY_PRESS_TEXTURE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

// Essa funcao se tornou obsoleta na aula 7 (Texture Loading and Rendering) junto com algumas outras linhas de codigo que foram apagadas
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

void close() {
    // Libera imagem carregada
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

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
            gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT];

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
                    // Usuario pressionou uma tecla
                    else if( e.type == SDL_KEYDOWN )
                    {
                        // Seleciona a textura baseada na tecla
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_UP ];
                            break;

                            case SDLK_DOWN:
                            gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_DOWN ];
                            break;

                            case SDLK_LEFT:
                            gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_LEFT ];
                            break;

                            case SDLK_RIGHT:
                            gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_RIGHT ];
                            break;

                            default:
                            gTexture = gKeyPressTextures[ KEY_PRESS_TEXTURE_DEFAULT ];
                            break;
                        }
                    }
                }

                // Limpa a tela
                SDL_RenderClear(gRenderer);

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