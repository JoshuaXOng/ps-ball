#include <SDL2/SDL.h>

#include <memory>
#include <iostream>
#include <math.h>

#include "model_interfaces.hpp"

//
// B2Entity class
//

void B2Entity::spawn(b2World& world) {    
    b2BodyDef* bodyDef = this->bodyDef;
    b2Body* body = world.CreateBody(bodyDef);
    delete bodyDef;

    this->body = body;
    b2FixtureDef* fixtureDef = this->fixtureDef;
    body->CreateFixture(fixtureDef);
    delete fixtureDef;
};

//
//
// B2Entity class Updateable a-b-class member implementation

void B2Entity::onUpdate(std::vector<Updateable*> updateables) {
    this->destinationArea->x = this->body->GetPosition().x;
    this->destinationArea->y = this->body->GetPosition().y;
    this->rotation = (this->body->GetAngle() / M_PI) * 180;
};

//
// Spaceship abstract class...
//
