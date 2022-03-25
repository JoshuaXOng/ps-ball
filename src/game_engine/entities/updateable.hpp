#pragma once
#include <SDL2/SDL.h>
#include <utility>
#include "./entity.hpp"

class Updateable : public Entity {
  public:
    Updateable(int id, std::string name, Position position, float angle, TwoDVector size, float scale) 
    : Entity(id, name, position, angle, size, scale) {};
      
    virtual void onUpdate(SDL_Event event) = 0;
};