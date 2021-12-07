#pragma once
#include <SDL2/SDL.h>

#include <vector>
#include <utility>

#include "../game_engine/game_engine.hpp"
#include "../game_engine/game_engine_interfaces.hpp"
#include "model_interfaces.hpp"
#include "../utils/physics_utils.hpp"

class Ball : public Updateable, Renderable, Physicsable {

    public:

        //
        // Class properties
        //

        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect* destinationArea;
        double* angleOfRotation;

        SDL_Point* position;
        TwoDVector* velocity;
        TwoDVector* acceleration;

        TwoDVector* netForce;
        std::vector<TwoDVector*> forces;
        float mass;

        float* rotationalDisplacement;
        float* rotationalVelocity;
        float* rotationalAcceleration;

        //
        // Default constructor and destructor
        //

        /**
         * @brief Construct a new Ball object
         * 
         * @param filePathToSurface This is relative from the working directory.
         */
        Ball(
            const char* filePathToSurface, SDL_Renderer* renderer,
            SDL_Rect* destinationArea, double* angleOfRotation
        );

        ~Ball();

        //
        // Ball methods
        //

        void teleport();   

        //
        // Updateable virtual members
        //

        void onUpdate(std::vector<Updateable*> updateables);
        bool getIsCollidable();
        SDL_Rect* getDestinationArea();

    private:

        //
        // Renderable virtual members
        //

        SDL_Renderer* getRenderer();
        SDL_Texture* getTexture();
        // SDL_Rect* Ball::Renderable::getDestinationArea();
        double getAngleOfRotation();

        //
        // Physicsable virtual members
        //     

        SDL_Point* getPosition();
        TwoDVector* getVelocity();
        TwoDVector* getAcceleration();

        TwoDVector* getNetForce();
        std::vector<TwoDVector*> getForces();
        float getMass();

        float* getRotationalDisplacement();
        float* getRotationalVelocity();
        float* getRotationalAcceleration();

};