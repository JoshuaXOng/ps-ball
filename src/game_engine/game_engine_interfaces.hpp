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

        // WHAT THE FUCK...
        // WHAT THE FUCK... If not initialized...
        // WHAT THE FUCK...
        // bool isCollidable = true;

        // WHAT THE FUCK...
        // WHAT THE FUCK... If not initialized...
        // WHAT THE FUCK...
        // SDL_Rect destinationArea = { 0, 0, 0, 0 };

        virtual void onUpdate(std::vector<Updateable*> updateables) = 0;

        virtual bool getIsCollidable() = 0;
        void setIsCollidable();

        virtual SDL_Rect* getDestinationArea() = 0;
        void setDestinationArea();

        // virtual std::vector<int> getForces();
        // virtual std::vector<int> getMass();
        // virtual std::vector<int> getAccelerationComponents();
        // virtual std::vector<int> getVelocityComponents();
        // virtual std::vector<int> getPositionComponents();

};

class Renderable {

    public: 

        virtual void onRender() { };

};