#include "globals.hpp"

SDL_Window *h_window = NULL;
SDL_Renderer *h_renderer = NULL;
SDL_Event event;

TTF_Font *font = NULL;
SDL_Color text_color = { 255, 255, 255, 0 };

int state_ID = STATE_NULL;
int next_state = STATE_NULL;

GS *current_state = NULL;