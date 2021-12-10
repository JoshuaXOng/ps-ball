#pragma once
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include "model_interfaces.hpp"
#include "../game_engine/game_engine_interfaces.hpp"

class Square : public B2Entity, public Renderable {

    public: 
        
        Square(const char* filePathToSurface, SDL_Renderer* renderer, SDL_Rect* destinationArea, double angleOfRotation);
        ~Square();

    private:

        b2FixtureDef* getSquareFixtureDef();

        //
        // B2Entity virtual members
        //

        void onUpdate(std::vector<Updateable*> updateables);

};