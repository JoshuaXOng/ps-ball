#pragma once
#include <SDL2/SDL.h>
#include <utility>
#include <string>
#include "./entity.hpp"

class Renderable : public Entity {
  public:
    std::string filePathToSurface;
    SDL_Texture* texture; // this->texture = SDLUtils::createTexture(filePathToSurface, this->renderer);
    
    Renderable(int id, std::string name, Position position, float angle, TwoDVector size, float scale) 
      : Entity(id, name, position, angle, size, scale) {};
      
    virtual void onRender() = 0;
};