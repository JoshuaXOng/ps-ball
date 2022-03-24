#pragma once
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <utility>
#include "./updateable.hpp"
#include "../utils.hpp"

class Physicsable : public Entity {
  public:
    b2BodyDef* bodyDef;
    b2Body* body;
    b2FixtureDef* fixtureDef;
    // joints

    Physicsable(int id, std::string name, Position position, float angle, TwoDVector size, float scale) 
      : Entity(id, name, position, angle, size, scale) {};

    void onResolution() {
      if (this->body) {
        this->position.first = this->body->GetPosition().x;
        this->position.second = this->body->GetPosition().y;
        this->angle = this->body->GetAngle();
      }
    };
};
