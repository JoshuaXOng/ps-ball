#include <SDL2/SDL.h>

#include "entity_factory.hpp"
#include "../models/ball.hpp"

Ball* EntityFactory::createBlueBall(
    SDL_Renderer* renderer, SDL_Rect creationArea, 
    double rotation, SDL_Point pointOfRotation
) {
    return new Ball(
        "assets/blue_ball.png", renderer, 
        creationArea, rotation, pointOfRotation
    );
}