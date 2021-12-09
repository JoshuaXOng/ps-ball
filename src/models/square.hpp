#pragma once
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include "model_interfaces.hpp"
#include "../game_engine/game_engine_interfaces.hpp"

class Square : public B2Entity, Updateable, Renderable {

    public: 

        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect* destinationArea;

        b2Body* body;
        
        SDL_Point topLeftPoint;
        SDL_Point centerPoint;
        SDL_Rect size;
        double* angleOfRotation;

        Square(SDL_Renderer* renderer, SDL_Rect* destinationArea, double* angleOfRotation);
        ~Square();

    private:

        //
        // B2Entity virtual members 
        //

        float getDensity();
        float getFriction();

        b2BodyDef* getBodyDef();
        b2Body* getBody();
        b2PolygonShape* getShape();
        b2FixtureDef* getFixtureDef();

        void setBody(b2Body* body);

        //
        // Updateable virtual members
        //

        void onUpdate(std::vector<Updateable*> updateables) {
            this->destinationArea->x = this->body->GetPosition().x;
            this->destinationArea->y = this->body->GetPosition().y;
            // this->angleOfRotation = this->body->GetAngle();
        };
        bool getIsCollidable() { return true; };
        // virtual SDL_Rect* getDestinationArea() = 0;

        //
        // Renderable virtual members
        //

        SDL_Renderer* getRenderer();
        SDL_Texture* getTexture();
        SDL_Rect* getDestinationArea();
        double getAngleOfRotation();

};