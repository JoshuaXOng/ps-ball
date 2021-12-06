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

Ball::Ball(
    const char* filePathToSurface, SDL_Renderer* sdlRenderer,
    SDL_Rect destinationArea, double angleOfRotation, SDL_Point pointOfRotation
) {
    this->sdlRenderer = sdlRenderer;
    this->sdlTexture = SdlScreenUtils::createTexture(filePathToSurface, sdlRenderer);
    this->destinationArea = destinationArea;
    this->angleOfRotation = angleOfRotation;
    // this->pointOfRotation = &pointOfRotation;
    SDL_Point test = { this->destinationArea.x + 50, this->destinationArea.y + 50 };
    this->pointOfRotation = &test;
}

Ball::~Ball() { }

void Ball::onUpdate(std::vector<Updateable*> updateables) {
    
    // this->destinationArea.y += 1;

    // SDL_Point point = PhysicsUtils::interpolatePoint({ x, y }, { destinationArea.x, destinationArea.y });
    // this->destinationArea.x += point.x;
    // this->destinationArea.y += point.y;
    // SDL_Rect test = { 100, 100, 100, 100 };
    // if (SDL_HasIntersection(&this->destinationArea, &test))
    //     std::cout << "Contact" << std::endl;
    
    float netYForce = 0;
    for (std::pair<std::pair<float, float>, std::pair<float, float>> force : this->forces) {
        netYForce += force.first.second;
    }
    float yAcceleration = netYForce / this->mass;
    this->velocityComponents.second += yAcceleration;
    this->destinationArea.y += this->velocityComponents.second; 

    float netXForce = 0;
    for (std::pair<std::pair<float, float>, std::pair<float, float>> force : this->forces) {
        netXForce += force.first.first;
    }
    float xAcceleration = netXForce / this->mass;
    this->velocityComponents.first += xAcceleration;
    this->destinationArea.x += this->velocityComponents.first; 

    float netMoment = 0;
    for (std::pair<std::pair<float, float>, std::pair<float, float>> force : this->forces) {
        float x = (force.second.first - 50) * -1 * force.first.second;
        netMoment += x;
        float y = (force.second.second - 50) * force.first.first;
        netMoment += y;
    }
    // std::cout << netMoment << std::endl;
    this->angleOfRotation += -netMoment / 500;
    

    if (this->destinationArea.y > 500) {
        this->forces = { 
            { { 0, 9.8 }, { 50, 50 } },
            { { -2, -9.8 }, { 80, 50 } } 
        };
        this->velocityComponents.second = 0;
        // int offset = this->destinationArea.y - 500;
        // this->destinationArea.y -= offset;
    }

    for (Updateable* updateable : updateables) {
        // std::cout << updateable->getIsCollidable() << std::endl;
        // Ball* test = (Ball*) updateable;
        // std::cout << (*updateable->getDestinationArea()).y << std::endl;
        if (this != updateable && SDL_HasIntersection(this->getDestinationArea(), updateable->getDestinationArea())) {
            std::cout << "Contact" << std::endl;
            this->destinationArea.y -= 1;
        }
    }

    // this->pointOfRotation = { this->destinationArea.x + 50, this->destinationArea.y + 50 };

}

void Ball::onRender() {
    SDL_Point test = { this->destinationArea.x + 50, this->destinationArea.y + 50 };
    SDL_RenderCopyEx(this->sdlRenderer, this->sdlTexture, 
        NULL, &this->destinationArea, 
        this->angleOfRotation, NULL, SDL_FLIP_NONE
    );
}