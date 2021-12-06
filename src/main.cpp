#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <any>

#include "game_engine/game_engine.hpp"
#include "utils/sdl_utils.hpp"
#include "application_constants.hpp"
#include "utils/math_utils.hpp"
#include "utils/keyboard_utils.hpp"
#include "utils/time_utils.hpp"

int main(int argc, char** argv) {

    GameEngine* gameEngine = new GameEngine();
    gameEngine->startMainWindow(
        MAIN_SDL_WINDOW_TITLE, 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        INITIAL_SDL_WINDOW_WIDTH, INITIAL_SDL_WINDOW_HEIGHT, 0
    );

    while (gameEngine->getIsMainWindowRunning()) 
        gameEngine->tick();

    gameEngine->terminate();

    return GOOD_EXIT;

}


