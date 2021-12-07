#include <SDL2/SDL.h>

#include <vector>
#include <math.h>

#include "geometry_utils.hpp"

std::vector<SDL_Point> GeometryUtils::calcPointsOfIntersection(std::vector<SDL_Point> firstShape, std::vector<SDL_Point> secondShape) {
    for (SDL_Point pointFs : firstShape) {
        for (SDL_Point pointSs : secondShape) {
            if (GeometryUtils::arePointsClose(pointFs, pointSs, 1)) {
                line intersection
            }    
        }
    }
};

std::vector<std::vector<SDL_Point>> GeometryUtils::calcAreasOfIntersection(std::vector<SDL_Point> firstShape, std::vector<SDL_Point> secondShape) {
    throw "Not implemented";
};

bool GeometryUtils::arePointsClose(SDL_Point firstPoint, SDL_Point secondPoint, float delta) {
    return sqrt(pow(firstPoint.x - secondPoint.x, 2) + pow(firstPoint.y - secondPoint.y, 2)) < delta;
};