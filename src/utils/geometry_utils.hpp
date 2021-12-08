#pragma once
#include <SDL2/SDL.h>

#include <vector>

class GeometryUtils {

    static std::vector<SDL_Point> calcPointsOfContact();

    // static std::vector<SDL_Point> calcPointsOfIntersection(std::vector<SDL_Point> firstShape, std::vector<SDL_Point> secondShape);

    static std::vector<std::vector<SDL_Point>> calcAreasOfIntersection(std::vector<SDL_Point> firstShape, std::vector<SDL_Point> secondShape);

    static bool arePointsClose(SDL_Point firstPoint, SDL_Point secondPoint, float delta);

};