#pragma once
#include <utility>
#include "./entity.hpp"

class Updateable : public Entity {
  public:
    Updateable(int id, std::string name, Position position, int angle, float scale) 
      : Entity(id, name, position, angle, scale) {};
      
    virtual void onUpdate() = 0;
};