#include <SDL2/SDL.h>

#include <memory>
#include <iostream>

#include "model_interfaces.hpp"

//
// Physicsable linear update methods
//

void Physicsable::resolvePosition() {
    SDL_Point* position = this->getPosition();
    TwoDVector* velocity = this->getVelocity();
    position->x += velocity->xComponent;
    position->y += velocity->yComponent;
};

void Physicsable::resolveVelocity() {
    TwoDVector* velocity = this->getVelocity();
    TwoDVector* acceleration = this->getAcceleration();
    velocity->xComponent += acceleration->xComponent;
    velocity->yComponent += acceleration->yComponent;
}

void Physicsable::resolveAcceleration() {
    TwoDVector* acceleration = this->getAcceleration();
    TwoDVector* netForce = this->getNetForce();
    acceleration->xComponent = netForce->xComponent / this->getMass();
    acceleration->yComponent = netForce->yComponent / this->getMass();
}

void Physicsable::resolveNetForce() {
    TwoDVector* netForce = this->getNetForce();
    for (TwoDVector* force : this->getForces()) {
        netForce->xComponent += force->xComponent;
        netForce->yComponent += force->yComponent;
    }
};

//
// Physicsable rotational update methods
//

void Physicsable::resolveRotationalDisplacement() { 

};
// float calcRotationalDisplacement(SDL_Point centerOfRotation) {
//     float netMoment = 0;
//     for (std::pair<std::pair<float, float>, std::pair<float, float>> force : this->getForces()) {
//         netMoment += -1 * (force.second.first - centerOfRotation.x) * force.first.second;
//         netMoment += (force.second.second - centerOfRotation.y) * force.first.first;
//     };
//     return netMoment / 500;
// }

//
// Physicsable protected methods
//

void Physicsable::resolveEverything() {
    this->resolveNetForce();
    this->resolveAcceleration();
    this->resolveVelocity();
    this->resolvePosition();
    this->resolveRotationalDisplacement();
};

//
// B2Entity class
//

void B2Entity::spawn(b2World& world) {    
    
    //
    // Reference vs pointer...
    // Use pass-by-pointer if NULL is a valid parameter value or if you want to reassign the pointer.
    //

    // b2Vec2 grav(0, 10);
    // b2World* test = new b2World(grav);
    // world = *test;
    // std::cout << &world << std::endl;
    // std::cout << &*test << std::endl;

    //
    // Actual method code
    //

    b2BodyDef* bodyDef = this->getBodyDef();
    b2Body* body = world.CreateBody(bodyDef);
    this->setBody(body);

    b2FixtureDef* fixtureDef = this->getFixtureDef();
    body->CreateFixture(fixtureDef);

};

void B2Entity::spawn(b2World* world) {    
    
    b2BodyDef* bodyDef = this->getBodyDef();
    b2Body* body = world->CreateBody(bodyDef);
    this->setBody(body);

    b2FixtureDef* fixtureDef = this->getFixtureDef();
    this->getBody()->CreateFixture(fixtureDef);

};

