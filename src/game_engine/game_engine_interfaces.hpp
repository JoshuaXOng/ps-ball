#pragma once
#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "./game_engine.hpp"
#include "./state_repository.hpp"

//
// Updateable class
//

class Updateable {

    public: 

        virtual void onUpdate(std::vector<Updateable*> updateables) = 0;

        bool isCollidable;

    protected:

        SDL_Rect* destinationArea;
        double rotation;

};

//
// Renderable class
//

class Renderable {

    public: 

        Renderable(const char* filePathToSurface, SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation);
        ~Renderable();

        void onRender();

    protected:

        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect* destinationArea;
        double rotation;

};