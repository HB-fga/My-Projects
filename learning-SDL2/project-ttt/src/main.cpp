#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

#include "globals.hpp"
#include "utils.hpp"

#include "HTexture.hpp"

#include "GS.hpp"
#include "GSIntro.hpp"
#include "GSTitle.hpp"

int main( int argc, char* args[] ) {

    bool success = true;

    if( !init() )
    {
        printf("failed init\n");
        success = false;
    }

    if( success )
    {
        state_ID = STATE_INTRO;

        current_state = new GSIntro();

        while( state_ID != STATE_EXIT )
        {
            current_state->handleEvents();

            current_state->logic();

            change_state();

            current_state->render();
        }
    }

    close();

    return 0;
}