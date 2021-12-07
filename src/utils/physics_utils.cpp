#include <SDL2/SDL.h>

#include "physics_utils.hpp"
#include "iostream"
#include <math.h>

//
// PhysicsUtils class
//

float PhysicsUtils::calcDistance(SDL_Point initialPos, SDL_Point finalPos) {
    int xDistance = finalPos.x - initialPos.x;
    int yDistance = finalPos.y - initialPos.y;
    return sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}

float PhysicsUtils::calcSpeed(float distance, int time) {
    return distance / time;
}

double PhysicsUtils::calcAcceleration(float initialVelocity, float finalVelocity, int time) {
    return (finalVelocity - initialVelocity) / time;   
}

SDL_Point PhysicsUtils::interpolatePoint(SDL_Point target, SDL_Point current) {
    int xCoord = (target.x - current.x) / 50;
    int yCoord = (target.y - current.y) / 50;
    return { xCoord, yCoord };
}

//
// TwoDVector class
//

TwoDVector::TwoDVector(float xComponent, float yComponent, SDL_Point position) {
    this->xComponent = xComponent;
    this->yComponent = yComponent;
    this->position = position;
};

float TwoDVector::calcMagnitude() {
    return sqrt(pow(this->xComponent, 2) + pow(this->yComponent, 2));
};
