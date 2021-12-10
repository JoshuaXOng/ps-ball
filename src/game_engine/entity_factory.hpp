#pragma once
#include <SDL2/SDL.h>

#include "../models/ball.hpp"

class EntityFactory {
    
    public:

        static Ball* createBlueBall(SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation);

};