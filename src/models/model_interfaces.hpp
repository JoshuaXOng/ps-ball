#pragma once
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include <vector>
#include <utility>

#include "../utils/physics_utils.hpp"

//
// Physicsable abstract class
//

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

//
// Box2D abstract class
//

class B2Entity {

    public:

        void spawn(b2World& world);
        void spawn(b2World* world);

    private:

        virtual float getDensity() = 0;
        virtual float getFriction() = 0;

        virtual b2BodyDef* getBodyDef() = 0;
        virtual b2Body* getBody() = 0;
        virtual b2PolygonShape* getShape() = 0;
        virtual b2FixtureDef* getFixtureDef() = 0;

        virtual void setBody(b2Body* body) = 0;

};
