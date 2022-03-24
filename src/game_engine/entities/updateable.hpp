#pragma once
#include <utility>
#include "./entity.hpp"

class Updateable : public Entity {
  public:
    Updateable(int id, std::string name, Position position, float angle, TwoDVector size, float scale) 
      : Entity(id, name, position, angle, size, scale) {};
      
    virtual void onUpdate() = 0;
};