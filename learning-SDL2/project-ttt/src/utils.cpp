#include "utils.hpp"

#include "globals.hpp"
#include "GSIntro.hpp"
#include "GSTitle.hpp"

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL not initialized! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        h_window = SDL_CreateWindow( "Janelow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( h_window == NULL )
        {
            printf( "Window not created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            h_renderer = SDL_CreateRenderer( h_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( h_renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( h_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init(imgFlags) & imgFlags ) )
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

void close()
{
    SDL_DestroyRenderer( h_renderer );
    SDL_DestroyWindow( h_window );
    h_window = NULL;
    h_renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

void set_next_state( int new_state )
{
    //If the user doesn't want to exit
    if( next_state != STATE_EXIT )
    {
        //Set the next state
        next_state = new_state;
    }
}

void change_state()
{
    //If the state needs to be changed
    if( next_state != STATE_NULL )
    {
        //Delete the current state
        if( next_state != STATE_EXIT )
        {
            delete current_state;
        }

        //Change the state
        switch( next_state )
        {
            case STATE_INTRO:
                current_state = new GSIntro();
                break;

            case STATE_TITLE:
                current_state = new GSTitle();
                break;
        }

        state_ID = next_state;

        next_state = STATE_NULL;
    }
}