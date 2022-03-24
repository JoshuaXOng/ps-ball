#pragma once
#include <iostream>
#include <utility>
#include <string>
#include "../types.hpp"

class Entity {
  public:
    int id;
    std::string name;
    Position position;
    int angle;
    float scale;

    Entity(int id, std::string name, Position position, int angle, float scale) {
      this->id = id;
      this->name = name;
      this->position = position;
      this->angle = angle;
      this->scale = scale;
    };
};