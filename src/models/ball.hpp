#pragma once
#include <SDL2/SDL.h>

#include <vector>
#include <utility>

#include "../game_engine/game_engine_interfaces.hpp"
#include "model_interfaces.hpp"
#include "../utils/physics_utils.hpp"

class Ball : public Renderable, public B2Entity {

    public:

        Ball(const char* filePathToSurface, SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation);
        ~Ball();

        //
        // B2Entity virtual members
        //
        
        void onUpdate(std::vector<Updateable*> updateables);

    private:

        //
        // Ball utility methods
        //

        b2BodyDef* getBallBodyDef(SDL_Rect& destinationArea);
        b2Shape* getBallShape(SDL_Rect& destinationArea);
        b2FixtureDef* getBallFixtureDef();

};