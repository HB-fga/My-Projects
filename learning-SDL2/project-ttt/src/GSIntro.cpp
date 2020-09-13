#include "GSIntro.hpp"
#include "globals.hpp"
#include "utils.hpp"

GSIntro::GSIntro()
{
    if( !background.loadFromFile( "res/bg.png" ) );
    {
        printf( "Failed to load bg texture!\n" );
    }

    font = TTF_OpenFont("res/pixel-font.ttf", 20);
    if( font == NULL )
        printf( "Failed to load font!\n" );
    else
    {
        message.loadFromRenderedText( "HB studios presents...", text_color );
    }
    
}

GSIntro::~GSIntro()
{
    background.free();
    message.free();
}

void GSIntro::handleEvents()
{

    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT )
        {
            set_next_state( STATE_EXIT );
        }
        else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
        {
            set_next_state( STATE_TITLE );
        }
    }
}

void GSIntro::logic()
{

}

void GSIntro::render()
{
    SDL_RenderClear( h_renderer );

    background.render( 0, 0 );
    message.render( ( SCREEN_WIDTH - message.getWidth() ) / 2, ( SCREEN_HEIGHT - message.getHeight() ) / 2 );

    SDL_RenderPresent( h_renderer );
}