#include "GSTitle.hpp"
#include "globals.hpp"
#include "utils.hpp"

GSTitle::GSTitle()
{
    // TODO
    // background.loadFromFile( ".png" );

    font = TTF_OpenFont("res/pixel-font.ttf", 20);
    if( font == NULL )
        printf( "Failed to load font!\n" );
    else
    {
        message.loadFromRenderedText( "Title...", text_color );
    }

}

GSTitle::~GSTitle()
{
    background.free();
    message.free();
}

void GSTitle::handleEvents()
{
    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT )
        {
            set_next_state( STATE_EXIT );
        }
        else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
        {
            // TODO
            // set_next_state( STATE_INTRO );
        }
    }
}

void GSTitle::logic()
{

}

void GSTitle::render()
{
    SDL_RenderClear( h_renderer );

    background.render( 0, 0 );
    message.render( ( SCREEN_WIDTH - message.getWidth() ) / 2, ( SCREEN_HEIGHT - message.getHeight() ) / 2 );

    SDL_RenderPresent( h_renderer );
}