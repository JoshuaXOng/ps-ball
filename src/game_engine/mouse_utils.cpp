#include <SDL2/SDL.h>

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <exception>
#include <utility>

#include "mouse_utils.hpp"
#include "../utils/physics_utils.hpp"
#include "../utils/time_utils.hpp"

// MOUSE TELEMETRY PUBLIC
// MOUSE TELEMETRY PUBLIC
// MOUSE TELEMETRY PUBLIC

/**
 * @brief Constructor.
 * Note:
 *  - Everything that regards time will be in units milliseconds
 */
MouseTelemetry::MouseTelemetry(int pollingInterval, int storageSize) {
    
    if (storageSize <= 2) 
        throw std::runtime_error("MouseTelemetry object should be init'd with more that 2 storage size.");
    if (pollingInterval < 100)
        throw std::runtime_error("Polling interval cannot be lower than 100ms.");

    this->pollingInterval = pollingInterval;
    TimeUtils::setIntervalThreaded(this->pollingInterval, [=]() {
        this->recordPosition();
    });

    SDL_Point currentPosition; 
    SDL_GetMouseState(&currentPosition.x, &currentPosition.y);
    for (int i = 0; i < storageSize; i++)
        this->previousPositions.push_back(currentPosition);

    assert(this->previousPositions.size() == storageSize);

};

MouseTelemetry::~MouseTelemetry() { };

void MouseTelemetry::printPreviousPositions() {
    std::cout << "========== Mouse Positions ==========" << std::endl;   
    for (SDL_Point point : MouseTelemetry::previousPositions)
        std::cout << "x position: " << point.x << ", y position: " << point.y << std::endl;
    std::cout << "========== End Mouse Positions ==========" << std::endl;   
};

SDL_Point MouseTelemetry::getCurrentPosition() {
    SDL_Point position; 
    SDL_GetMouseState(&position.x, &position.y);
    return { position.x, position.y };
};

std::pair<float, float> MouseTelemetry::getCurrentVelocityComponents() {
    return this->getVelocityComponents(0);
};

float MouseTelemetry::getCurrentSpeed() {
    return this->getSpeed(0);
};

double MouseTelemetry::getCurrentAcceleration() {
    float newestSpeed = this->getCurrentSpeed();
    float laterSpeed = this->getSpeed(1);
    return PhysicsUtils::calcAcceleration(laterSpeed, newestSpeed, this->pollingInterval);
};

std::pair<float, float> MouseTelemetry::getCurrentAccelerationComponents() {

    std::pair<float, float> currentVelocityComponents = this->getCurrentVelocityComponents();
    std::pair<float, float> previousVelocityComponents = this->getVelocityComponents(1);

    float xAcceleration = (currentVelocityComponents.first - previousVelocityComponents.first) / this->pollingInterval;
    float yAcceleration = (currentVelocityComponents.second - previousVelocityComponents.second) / this->pollingInterval;

    return std::make_pair(xAcceleration, yAcceleration);

};

// MOUSE TELEMETRY PRIVATE 
// MOUSE TELEMETRY PRIVATE
// MOUSE TELEMETRY PRIVATE

float MouseTelemetry::getSpeed(int offset) {

    SDL_Point mostRecentPosition = this->previousPositions.end()[-1 - offset];
    SDL_Point secondMostRecentPosition = this->previousPositions.end()[-2 - offset];

    float distance = PhysicsUtils::calcDistance(mostRecentPosition, secondMostRecentPosition);
    float speed = PhysicsUtils::calcSpeed(distance, this->pollingInterval);

    return speed;

};

std::pair<float, float> MouseTelemetry::getVelocityComponents(int offset) {

    SDL_Point currentPosition = this->previousPositions.end()[-1 - offset];
    SDL_Point previousPosition = this->previousPositions.end()[-2 - offset];

    int xDisplacement = currentPosition.x - previousPosition.x;
    float xVelocity = xDisplacement / this->pollingInterval;
    int yDisplacement = currentPosition.y - previousPosition.y;
    float yVelocity = yDisplacement / this->pollingInterval;
    
    return std::make_pair(xVelocity, yVelocity);

};

void MouseTelemetry::recordPosition() {
    SDL_Point position = MouseTelemetry::getCurrentPosition();
    MouseTelemetry::previousPositions.push_back(position);
    MouseTelemetry::previousPositions.erase(MouseTelemetry::previousPositions.begin());
};

