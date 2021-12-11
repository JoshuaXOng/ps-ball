#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include <iostream>
#include <memory>
#include <utility>

#include "ball.hpp"
#include "../utils/sdl_utils.hpp"
#include "../utils/physics_utils.hpp"
#include "../game_engine/game_engine.hpp"
#include "../game_engine/game_engine_interfaces.hpp"

class GameEngine;

//
// Ball Class
//

Ball::Ball(const char* filePathToSurface, SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation) 
: Renderable(filePathToSurface, renderer, destinationArea, rotation), B2Entity(destinationArea, rotation) { 
    this->density = 1.0f;
    this->friction = 0.3f;
    this->bodyDef = getBallBodyDef(*this->Renderable::destinationArea); // lvalue... rvalue
    this->shape = getBallShape(*this->Renderable::destinationArea); // lvalue... rvalue
    this->fixtureDef = this->getBallFixtureDef();
};

Ball::~Ball() { };

//
// Ball utility methods implementations
//

b2BodyDef* Ball::getBallBodyDef(SDL_Rect& destinationArea) {
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(destinationArea.x, destinationArea.y);
    return bodyDef;
};

b2Shape* Ball::getBallShape(SDL_Rect& destinationArea) {
    if (destinationArea.h != destinationArea.w) 
        throw std::runtime_error("Ball entity's shape is not a perfect circle.");

    b2CircleShape circle;
    circle.m_radius = destinationArea.w / 2;
    b2CircleShape* circleP = new b2CircleShape(circle);
    return circleP;
};

b2FixtureDef* Ball::getBallFixtureDef() {
    if (this->shape == NULL)
        throw "getBallFixture(...) is being called but the required props are NULL.";

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = this->shape;
    fixtureDef->density = this->density;
    fixtureDef->friction = this->friction;
    return fixtureDef;
};

//
// B2Entity virtual implementations
//

void Ball::onUpdate(std::vector<Updateable*> updateables) {
    this->B2Entity::onUpdate(updateables);
    this->Renderable::rotation = (this->body->GetAngle() / 3.14) * 180;
};
