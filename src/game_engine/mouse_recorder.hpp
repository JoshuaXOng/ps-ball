#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <exception>
#include <deque>
#include "time_utils.hpp"
#include "physics_utils.hpp"
#include "types.hpp"

class MouseRecorder {
	public:
		MouseRecorder() {
			for (int i = 0; i < this->capacity; i++)
				this->updatePrevPositions();
			TimeUtils::setIntervalThreaded(this->pollingInterval, [=]() {
				this->updatePrevPositions();
			});
		};
		~MouseRecorder() {};

		SDL_Point getCurrentPosition() {
			SDL_Point position; 
			SDL_GetMouseState(&position.x, &position.y);
			return position;
		};

		void printPreviousPositions(int num) {
			std::deque<SDL_Point>::iterator it = this->previousPositions.end();
			for (int i = 0; i < num; i++) {
				SDL_Point point = *it--;
				printf("Coordinates of mouse: %i, %i", point.x, point.y);
			}
		};

		TwoDVector getCurrentVelocity() {
			return this->getVelocity(0);
		};

		float getCurrentSpeed() {
			return this->getSpeed(0);
		};

		std::pair<float, float> getCurrentAcceleration() {
			return this->getAcceleration(0);
		};

	private:
		int pollingInterval = 50;
		int capacity = 100;
		std::deque<SDL_Point> previousPositions = {};

		void updatePrevPositions() {
			SDL_Point position = MouseRecorder::getCurrentPosition();
			MouseRecorder::previousPositions.push_back(position);
			if (this->previousPositions.size() > this->capacity)
				MouseRecorder::previousPositions.pop_front();
		};

		std::pair<float, float> getVelocity(int offset) {
			SDL_Point currentPosition = this->previousPositions.end()[-1 - offset];
			SDL_Point previousPosition = this->previousPositions.end()[-2 - offset];

			int xDisplacement = currentPosition.x - previousPosition.x;
			float xVelocity = xDisplacement / this->pollingInterval;
			int yDisplacement = currentPosition.y - previousPosition.y;
			float yVelocity = yDisplacement / this->pollingInterval;
			
			return std::make_pair(xVelocity, yVelocity);
		};

		float getSpeed(int offset) {
			SDL_Point currentPosition = this->previousPositions.end()[-1 - offset];
			SDL_Point previousPosition = this->previousPositions.end()[-2 - offset];

			float distance = PhysicsUtils::calcDistance(currentPosition, previousPosition);
			float speed = PhysicsUtils::calcSpeed(distance, this->pollingInterval);

			return speed;
		};

		std::pair<float, float> getAcceleration(int offset) {
			std::pair<float, float> currentVelocity = this->getVelocity(0 + offset);
			std::pair<float, float> previousVelocity = this->getVelocity(1 + offset);

			float xAcceleration = (currentVelocity.first - previousVelocity.first) / this->pollingInterval;
			float yAcceleration = (currentVelocity.second - previousVelocity.second) / this->pollingInterval;

			return std::make_pair(xAcceleration, yAcceleration);
		};
};