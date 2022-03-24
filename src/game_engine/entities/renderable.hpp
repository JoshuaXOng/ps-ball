#pragma once
#include <utility>
#include "./updateable.hpp"

class Renderable : public Updateable {
  public:
    Renderable(int id, std::string name, Position position, int angle, float scale) 
      : Updateable(id, name, position, angle, scale) {};
      
    virtual void onRender() = 0;
};