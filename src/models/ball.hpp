#pragma once
#include <SDL2/SDL.h>

#include <vector>
#include <utility>

#include "../game_engine/game_engine.hpp"
#include "../game_engine/game_engine_interfaces.hpp"
#include "model_interfaces.hpp"

class Ball : public Updateable, Renderable, Physicsable {

    public:

        SDL_Renderer* sdlRenderer;
        SDL_Texture* sdlTexture;

        SDL_Rect destinationArea = { 2, 2, 2, 2 };
        double angleOfRotation;
        SDL_Point* pointOfRotation;

        std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> forces = { 
            { { 0, 9.8 }, { 50, 50 } } 
        };
        std::pair<float, float> velocityComponents = { 0, 0 };
        float mass = 40;

        Ball(
            const char* filePathToSurface, SDL_Renderer* sdlRenderer,
            SDL_Rect destinationArea, double angleOfRotation, SDL_Point pointOfRotation
        );
        ~Ball();

        SDL_Rect* getDestinationArea() {
            return &this->destinationArea;
        }

        bool getIsCollidable() {
            return true;
        }

        void onUpdate(std::vector<Updateable*> updateables);

        void onRender();

        void teleport();

};