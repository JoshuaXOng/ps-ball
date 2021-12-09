#include <SDL2/SDL.h>

#include <iostream>

#include "game_engine_interfaces.hpp"

//
// Renderable class
//

void Renderable::onRender() {
    SDL_RenderCopyEx(
        this->getRenderer(), this->getTexture(),
        NULL, this->getDestinationArea(),
        this->getAngleOfRotation(), NULL, SDL_FLIP_NONE
    );
};