#pragma once
#include <SDL2/SDL.h>
#include <utility>
#include <string>
#include "./entity.hpp"

class Renderable : public Entity {
  public:
    SDL_Texture* texture;
    
    Renderable(int id, std::string name, Position position, float angle, TwoDVector size, float scale) 
    : Entity(id, name, position, angle, size, scale) {};
      
    virtual void onRender() = 0;
};