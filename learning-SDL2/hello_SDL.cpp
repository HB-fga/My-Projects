// Linha de compilacao
// g++ file.cpp -w -lSDL2 -lSDL2_image -o prog

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// constantes de cada superficie para cada tecla
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// Inicia a SDL e cria janela
bool init();

// Libera a midia e encerra a SDL
void close();

// Carrega as midias requisitadas
bool loadMedia();

// Carrega uma imagem individual
SDL_Surface* loadSurface( std::string path );

// Janela onde vamos renderizar
SDL_Window* gWindow = NULL;

// Superficie (surface) contida pela janela
SDL_Surface* gScreenSurface = NULL;

// Imagem exibida atualmente
SDL_Surface* gCurrentSurface = NULL;

// As imagens que correspondem a cada tecla
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

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
            // Inicia o carregamento PNG
            int imgFlags = IMG_INIT_PNG;
            if( !(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                // Pega superficie da janela
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }

    return success;
}

bool loadMedia()
{

    bool success = true;

    // Carrega default
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("press.png");
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    // Carrega up
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    // Carrega down
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    // Carrega left
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    // Carrega right
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

SDL_Surface* loadSurface( std::string path ) {

    // Imagem final e otimizada
    SDL_Surface* optimizedSurface = NULL;

    // Carrega imagem
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Converte a superficie para o tamanho da tela
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
        
        // Libera superficie temporaria
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

void close() {
    // Libera imagem carregada
    SDL_FreeSurface(gCurrentSurface);
    gCurrentSurface = NULL;

    // Destroi janela
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Fecha a SDL
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

            // Seta a superficie atual como a default
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

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
                        // Seleciona superficie baseada na tecla
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;

                            default:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                        }
                    }
                }

                // Aplica a imagem atual
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
                
                // Atualiza a tela
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    // Libera recursos e fecha a SDL
    close();

    return 0;
}