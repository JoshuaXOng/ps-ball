#pragma once
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include "model_interfaces.hpp"

class BasicSpaceship : public B2Entity, public RenderableMulti {

    public: 

        BasicSpaceship(
            const std::vector<char*> filePathsToSurfaces, SDL_Renderer* renderer, 
            std::vector<SDL_Rect*> destinationAreas, std::vector<double> rotations
        );
        ~BasicSpaceship();

        void faceLocation(SDL_Point position);
        
        void moveTopGlobal();
        void moveRightGlobal();
        void moveBotGlobal();
        void moveLeftGlobal();

        void moveTopRelative();
        void moveRightRelative();
        void moveBotRelative();
        void moveLeftRelative();

        //
        // B2Entity virtual members
        //

        void onUpdate(std::vector<Updateable*> updateables);

};
