#pragma once
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include <vector>
#include <utility>

#include "../utils/physics_utils.hpp"
#include "../game_engine/game_engine_interfaces.hpp"

//
// Box2D abstract class
//

class B2Entity : public Updateable {

    public:

        B2Entity(SDL_Rect* destinationArea, double rotation);

        void spawn(b2World& world);

        //
        // Updateable abstract class members
        //

        void onUpdate(std::vector<Updateable*> updateables);

    protected:

        float density;
        float friction;

        b2BodyDef* bodyDef;
        b2Body* body;
        b2PolygonShape* shape;
        b2FixtureDef* fixtureDef;

};

//
// Spaceship abstract class
// 

class Spaceship {

    public: 

        void moveUp();
        void moveRight();
        void moveDown();
        void moveLeft();

};