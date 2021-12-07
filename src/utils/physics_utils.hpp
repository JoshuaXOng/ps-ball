#pragma once
#include <SDL2/SDL.h>

class PhysicsUtils {

    public:

        static float calcDistance(SDL_Point initialPos, SDL_Point finalPos);

        static float calcSpeed(float distance, int time);

        static double calcAcceleration(float initialVelocity, float finalVelocity, int time);

        static SDL_Point interpolatePoint(SDL_Point target, SDL_Point current);

};

class TwoDVector {

    public:

        float xComponent;
        float yComponent;

        SDL_Point position;

        TwoDVector(float xComponent, float yComponent, SDL_Point position);

        float calcMagnitude();

};