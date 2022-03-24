#pragma once
#include <stdio.h>
#include <functional>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>
#include <math.h>

class Utils {
  public:
    static float toRadians(float degrees) {
      return degrees * M_PI / 180;
    };

    static float toDegrees(float radians) {
      return radians * 180 / M_PI;
    };
};
