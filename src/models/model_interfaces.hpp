#pragma once
#include <SDL2/SDL.h>

#include <vector>
#include <utility>

#include "../utils/physics_utils.hpp"

class Physicsable {
    
    private:

        //
        // Class properties
        //

        virtual SDL_Point* getPosition() = 0;
        virtual TwoDVector* getVelocity() = 0;
        virtual TwoDVector* getAcceleration() = 0;

        virtual TwoDVector* getNetForce() = 0;
        virtual std::vector<TwoDVector*> getForces() = 0;
        virtual float getMass() = 0;

        virtual float* getRotationalDisplacement() = 0;
        virtual float* getRotationalVelocity() = 0;
        virtual float* getRotationalAcceleration() = 0;
        
    private: 

        //
        // Linear update methods                                                           
        //

        void resolvePosition();
        void resolveVelocity();
        void resolveAcceleration();
        void resolveNetForce();

        //
        // Rotation update methods
        //

        void resolveRotationalDisplacement();
    
    protected:

        void resolveEverything();

};