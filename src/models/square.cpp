#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include <iostream>

#include "square.hpp"
#include "../utils/sdl_utils.hpp"

Square::Square(SDL_Renderer* renderer, SDL_Rect* destinationArea, double* angleOfRotation ) {
    this->renderer = renderer;
    this->texture = SdlScreenUtils::createTexture("assets/blue_ball.png", this->renderer);
    this->destinationArea = destinationArea;
    this->topLeftPoint = { destinationArea->x, destinationArea->y };
    this->centerPoint = { 
        topLeftPoint.x + (destinationArea->w / 2), 
        topLeftPoint.y + (destinationArea->h / 2) 
    };
    this->size = { destinationArea->w, destinationArea->h };
    this->angleOfRotation = angleOfRotation;
};

Square::~Square() { };

//
// B2Entity abstract class implementation
//

float Square::getDensity() { return 1; };

float Square::getFriction() { return 0.3; };

b2BodyDef* Square::getBodyDef() {
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(this->centerPoint.x, this->centerPoint.y);
    return bodyDef;
};

b2Body* Square::getBody() { return this->body; };

b2PolygonShape* Square::getShape() {
    b2PolygonShape test;
    test.SetAsBox(destinationArea->w / 2, destinationArea->h / 2);
    b2PolygonShape* shape = new b2PolygonShape(test);
    return shape;
};

b2FixtureDef* Square::getFixtureDef() {
    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = this->getShape();
    fixtureDef->density = this->getDensity();
    fixtureDef->friction = this->getFriction();
    return fixtureDef;
};

void Square::setBody(b2Body* body) { this->body = body; };

//
// Updateable abstract class implementation
//

//
// Renderable abstract class implementation
//

SDL_Renderer* Square::getRenderer() { 
    std::cout << this->body->GetPosition().y << std::endl;
    // b2Vec2 test(100, 100);
    // this->body->SetLinearVelocity(test);
    return this->renderer; 
};

SDL_Texture* Square::getTexture() { return this->texture; };

SDL_Rect* Square::getDestinationArea() { return this->destinationArea; };

double Square::getAngleOfRotation() { return *this->angleOfRotation; };