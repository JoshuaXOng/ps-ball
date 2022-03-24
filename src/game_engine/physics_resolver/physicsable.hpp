#pragma once
#include <utility>

class Physicsable {
  public:
    float mass;
    virtual void onRender() = 0;
};