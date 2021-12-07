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

Ball::Ball(
    const char* filePathToSurface, SDL_Renderer* renderer,
    SDL_Rect* destinationArea, double* angleOfRotation
) {

    this->renderer = renderer;
    this->texture = SdlScreenUtils::createTexture(filePathToSurface, this->renderer);
    this->destinationArea = destinationArea;
    this->angleOfRotation = angleOfRotation;

    this->position = new SDL_Point({ this->destinationArea->x, this->destinationArea->y });
    this->velocity = new TwoDVector(0, 0, { 0, 0 });
    this->acceleration = new TwoDVector(0, 0, { 0, 0 });

    this->netForce = new TwoDVector(0, 0, { 0, 0 });
    this->forces = { new TwoDVector(0, 10, { 0, 0 }) };
    this->mass = 40;
    
    this->rotationalDisplacement = 0;
    this->rotationalVelocity = 0;
    this->rotationalAcceleration = 0;

}

Ball::~Ball() { }

//
// Updateable virtual implementations
//

void Ball::onUpdate(std::vector<Updateable*> updateables) {
    
    this->resolveEverything();
    this->destinationArea->x = this->position->x;
    this->destinationArea->y = this->position->y;

    // if (this->destinationArea.y > 500) {
    //     this->forces = { 
    //         { { 0, 9.8 }, { 50, 50 } },
    //         { { -2, -9.8 }, { 80, 50 } } 
    //     };
    //     this->velocityComponents.second = 0;
    //     // int offset = this->destinationArea.y - 500;
    //     // this->destinationArea.y -= offset;
    // }

    // for (Updateable* updateable : updateables) {
    //     // std::cout << updateable->getIsCollidable() << std::endl;
    //     // Ball* test = (Ball*) updateable;
    //     // std::cout << (*updateable->getDestinationArea()).y << std::endl;
    //     if (this != updateable && SDL_HasIntersection(this->getDestinationArea(), updateable->getDestinationArea())) {
    //         std::cout << "Contact" << std::endl;
    //         this->destinationArea.y -= 1;
    //     }
    // }

    // this->pointOfRotation = { this->destinationArea.x + 50, this->destinationArea.y + 50 };

}

bool Ball::getIsCollidable() {
    return true;
};

SDL_Rect* Ball::getDestinationArea() {
    return this->destinationArea;
};

//
// Renderable virtual implementations
//

SDL_Renderer* Ball::getRenderer() {
    return this->renderer;
};

SDL_Texture* Ball::getTexture() {
    return this->texture;
};

// SDL_Rect* Ball::Renderable::getDestinationArea() {
//     return ((Ball*) this)->destinationArea;
// };

double Ball::getAngleOfRotation() {
    return *this->angleOfRotation;
};

//
// Physicsable virtual implementations
// 

SDL_Point* Ball::getPosition() {
    return this->position;
};

TwoDVector* Ball::getVelocity() {
    return this->velocity;
};

TwoDVector* Ball::getAcceleration() {
    return this->acceleration;
};

TwoDVector* Ball::getNetForce() {
    return this->netForce;
};

std::vector<TwoDVector*> Ball::getForces() {
    return this->forces;
};

float Ball::getMass() {
    return this->mass;
};

float* Ball::getRotationalDisplacement() {
    return this->rotationalDisplacement;
}; 

float* Ball::getRotationalVelocity() {
    return this->rotationalVelocity;
};

float* Ball::getRotationalAcceleration() {
    return this->rotationalAcceleration;
};
