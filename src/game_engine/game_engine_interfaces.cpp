#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <stdexcept>

#include "game_engine_interfaces.hpp"
#include "../utils/sdl_utils.hpp"

//
// Updateable class implementation
//

Updateable::Updateable(SDL_Rect* destinationArea, double rotation) {
    if (destinationArea == NULL)
        throw std::runtime_error("destinationArea is a null pointer.");

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

// 
// RenderableMulti class implementation
//

RenderableMulti::RenderableMulti(
    const std::vector<char*> filePathsToSurfaces, SDL_Renderer* renderer, 
    std::vector<SDL_Rect*> destinationAreas, std::vector<double> rotations
) {
    if (
        filePathsToSurfaces.size() != destinationAreas.size() &&
        destinationAreas.size() != rotations.size()
    ) throw std::runtime_error("RenderableMulti vector inputs need to be the same length.");
    int allVectorsLengths = filePathsToSurfaces.size();

    this->renderer = renderer;
    for (int i = 0; i < allVectorsLengths; ++i) {
        this->textures.push_back(
            SdlScreenUtils::createTexture(filePathsToSurfaces.at(i), this->renderer)
        );
    }
    this->destinationAreas = destinationAreas;
    this->rotations = rotations;
};

RenderableMulti::~RenderableMulti() { };

void RenderableMulti::onRender() {
    if (this->renderer == NULL)
        throw std::runtime_error("The necessary properties to render this entity have not been assigned.");

    int allVectorsLength = this->textures.size();

    for (int i = 0; i < allVectorsLength; ++i) {
        SDL_RenderCopyEx( 
            this->renderer, this->textures.at(i),
            NULL, this->destinationAreas.at(i),
            this->rotations.at(i), NULL, SDL_FLIP_NONE
        );
    }
};