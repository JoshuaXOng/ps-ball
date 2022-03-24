#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <assert.h>
#include <exception>
#include "../utils/physics_utils.hpp"
#include "../utils/time_utils.hpp"

class MouseRecorder {
	public:
		MouseRecorder(int pollingInterval, int storageSize) {
			if (storageSize <= 2) 
				throw std::runtime_error("MouseRecorder object should be init'd with more that 2 storage size.");
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

			// assert(this->previousPositions.size() == storageSize);
		};
		~MouseRecorder() {};

		void printPreviousPositions() {
			std::cout << "========== Mouse Positions ==========" << std::endl;   
			for (SDL_Point point : MouseRecorder::previousPositions)
				std::cout << "x position: " << point.x << ", y position: " << point.y << std::endl;
			std::cout << "========== End Mouse Positions ==========" << std::endl;   
		};

		SDL_Point getCurrentPosition() {
			SDL_Point position; 
			SDL_GetMouseState(&position.x, &position.y);
			return { position.x, position.y };
		};

		std::pair<float, float> getCurrentVelocityComponents() {
			return this->getVelocityComponents(0);
		};

		float getCurrentSpeed() {
			return this->getSpeed(0);
		};

		double getCurrentAcceleration() {
			float newestSpeed = this->getCurrentSpeed();
			float laterSpeed = this->getSpeed(1);
			return PhysicsUtils::calcAcceleration(laterSpeed, newestSpeed, this->pollingInterval);
		};

		std::pair<float, float> getCurrentAccelerationComponents() {
			std::pair<float, float> currentVelocityComponents = this->getCurrentVelocityComponents();
    	std::pair<float, float> previousVelocityComponents = this->getVelocityComponents(1);

			float xAcceleration = (currentVelocityComponents.first - previousVelocityComponents.first) / this->pollingInterval;
			float yAcceleration = (currentVelocityComponents.second - previousVelocityComponents.second) / this->pollingInterval;

			return std::make_pair(xAcceleration, yAcceleration);
		};

	private:
		int pollingInterval;

		std::vector<SDL_Point> previousPositions = { };

		float getSpeed(int offset) {
			SDL_Point mostRecentPosition = this->previousPositions.end()[-1 - offset];
			SDL_Point secondMostRecentPosition = this->previousPositions.end()[-2 - offset];

			float distance = PhysicsUtils::calcDistance(mostRecentPosition, secondMostRecentPosition);
			float speed = PhysicsUtils::calcSpeed(distance, this->pollingInterval);

			return speed;
		};
		std::pair<float, float> getVelocityComponents(int offset) {
			SDL_Point currentPosition = this->previousPositions.end()[-1 - offset];
			SDL_Point previousPosition = this->previousPositions.end()[-2 - offset];

			int xDisplacement = currentPosition.x - previousPosition.x;
			float xVelocity = xDisplacement / this->pollingInterval;
			int yDisplacement = currentPosition.y - previousPosition.y;
			float yVelocity = yDisplacement / this->pollingInterval;
			
			return std::make_pair(xVelocity, yVelocity);
		};

		void recordPosition() {
			SDL_Point position = MouseRecorder::getCurrentPosition();
			MouseRecorder::previousPositions.push_back(position);
			MouseRecorder::previousPositions.erase(MouseRecorder::previousPositions.begin());
		};
};