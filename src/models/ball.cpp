#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <utility>

#include "ball.hpp"
#include "../utils/sdl_utils.hpp"
#include "../utils/physics_utils.hpp"
#include "../game_engine/game_engine.hpp"
#include "../game_engine/game_engine_interfaces.hpp"

class GameEngine;

//
// Ball Class
//

Ball::Ball(const char* filePathToSurface, SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation) 
: Renderable(filePathToSurface, renderer, destinationArea, rotation) { };

Ball::~Ball() { };

//
// B2Entity virtual implementations
//

void Ball::onUpdate(std::vector<Updateable*> updateables) {
    B2Entity::onUpdate(updateables);
};
