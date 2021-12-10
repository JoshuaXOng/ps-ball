#include <SDL2/SDL.h>

#include "entity_factory.hpp"
#include "../models/ball.hpp"

Ball* EntityFactory::createBlueBall(SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation) {
    return new Ball("assets/blue_ball.png", renderer, destinationArea, rotation);
}