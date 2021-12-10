#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "game_engine_interfaces.hpp"
#include "../utils/sdl_utils.hpp"

//
// Updateable class implementation
//

Updateable::Updateable(SDL_Rect* destinationArea, double rotation) {
    if (destinationArea == NULL)
        throw "Null pointer...";

    this->destinationArea = destinationArea;
    this->rotation = rotation;
};

//
// Renderable class implementation
//

Renderable::Renderable(const char* filePathToSurface, SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation) {
    this->renderer = renderer;
    this->texture = SdlScreenUtils::createTexture(filePathToSurface, this->renderer);
    this->destinationArea = destinationArea;
    this->rotation = rotation;
};

Renderable::~Renderable() { };

void Renderable::onRender() {
    if (this->renderer == NULL || this->texture == NULL || this->destinationArea == NULL)
        throw "The necessary properties to render this entity have not been assigned.";

    SDL_RenderCopyEx( 
        this->renderer, this->texture,
        NULL, this->destinationArea,
        this->rotation, NULL, SDL_FLIP_NONE
    );
};
