#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include <iostream>

#include "square.hpp"
#include "../utils/sdl_utils.hpp"

//
// Square class utilities
//

b2BodyDef* getSquareBodyDef(SDL_Rect& destinationArea) {
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(destinationArea.x, destinationArea.y);
    return bodyDef;
};

b2PolygonShape* getSquareShape(SDL_Rect& destinationArea) {
    b2PolygonShape shape;
    shape.SetAsBox(destinationArea.w / 2, destinationArea.h / 2);
    b2PolygonShape* shapeP = new b2PolygonShape(shape);
    return shapeP;
};

b2FixtureDef* Square::getSquareFixtureDef() {
    if (this->shape == NULL || this->density == NULL || this->friction == NULL)
        throw "getSquareFixture(...) is being called but the required props are NULL.";

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = this->shape;
    fixtureDef->density = this->density;
    fixtureDef->friction = this->friction;
    return fixtureDef;
};

//
// Square class
//

Square::Square(const char* filePathToSurface, SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation)
: Renderable(filePathToSurface, renderer, destinationArea, rotation) {
    this->density = 1.0f;
    this->friction = 0.3f;
    this->bodyDef = getSquareBodyDef(*this->Renderable::destinationArea); // lvalue... rvalue
    this->shape = getSquareShape(*this->Renderable::destinationArea); // lvalue... rvalue
    this->fixtureDef = this->getSquareFixtureDef();
};

Square::~Square() { };

//
// B2Entity class implementation
//

void Square::onUpdate(std::vector<Updateable*> updateables) {
    this->B2Entity::onUpdate(updateables);
};
