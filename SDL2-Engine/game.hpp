#ifndef GAME_HPP
#define GAME_HPP

#include "SDL2/SDL.h"

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handle_events();
    void update();
    void render();
    void clean();

    bool running() { return is_running; };

private:

    int cnt = 0;
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;

};

#endif