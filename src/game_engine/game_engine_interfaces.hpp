#pragma once
#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "./game_engine.hpp"
#include "./state_repository.hpp"

class Intervalable {

    public: 

        virtual void onInterval(int interval) { };

};

class Updateable {

    public: 

        virtual void onUpdate(std::vector<Updateable*> updateables) = 0;

        virtual bool getIsCollidable() = 0;

        virtual SDL_Rect* getDestinationArea() = 0;

};

class Renderable {

    public: 

        void onRender();

    private:

        virtual SDL_Renderer* getRenderer() = 0;
        virtual SDL_Texture* getTexture() = 0;
        virtual SDL_Rect* getDestinationArea() = 0;
        virtual double getAngleOfRotation() = 0;

};