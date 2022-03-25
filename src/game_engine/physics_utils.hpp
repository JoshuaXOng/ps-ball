#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

class PhysicsUtils {
	public:
		static float calcDistance(SDL_Point initialPos, SDL_Point finalPos) {
			int xDistance = finalPos.x - initialPos.x;
			int yDistance = finalPos.y - initialPos.y;
			return sqrt(pow(xDistance, 2) + pow(yDistance, 2));
		};

		static float calcSpeed(float distance, int time) {
			return distance / time;
		};

		static double calcAcceleration(float initialVel, float finalVel, int time) {
			return (finalVel - initialVel) / time;   
		};

		static SDL_Point interpolatePoint(SDL_Point target, SDL_Point current) {
			int xCoord = (target.x - current.x) / 50;
    	int yCoord = (target.y - current.y) / 50;
    	return { xCoord, yCoord };
		};
};
