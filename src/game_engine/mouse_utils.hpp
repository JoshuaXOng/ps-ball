#pragma once
#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <utility>

class MouseTelemetry {

    public:

        MouseTelemetry(int pollingInterval, int storageSize);
        ~MouseTelemetry();

        void printPreviousPositions();

        SDL_Point getCurrentPosition();
        std::pair<float, float> getCurrentVelocityComponents();
        float getCurrentSpeed();
        double getCurrentAcceleration();
        std::pair<float, float> getCurrentAccelerationComponents();

    private:

        int pollingInterval;

        std::vector<SDL_Point> previousPositions = { };

        float getSpeed(int offset);
        std::pair<float, float> getVelocityComponents(int offset);

        void recordPosition();

};