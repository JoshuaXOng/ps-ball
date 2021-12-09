#pragma once
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include <stdio.h>
#include <functional>
#include <vector>

#include "game_engine_interfaces.hpp"
#include "mouse_utils.hpp"
#include "state_repository.hpp"

class GameEngine {

    public:

        b2World* world;

        MouseTelemetry* mouseTelemetry;

        StateRepository* state;

        std::vector<Updateable*> updateables;
        std::vector<Renderable*> renderables;

        bool isRunning = false;
        bool isReadyToUpdate = false;
        bool isReadyToRender = false;

        int tickFrequency;

        GameEngine(int tickFrequency);
        ~GameEngine();

        void startMainWindow(const char* title, int xPos, int yPos, int width, int height, Uint32 sdlWindowFlags);
        
        void tick();

        void cleanUp();

    private:

        SDL_Window* window;
        SDL_Renderer* renderer;

        void handleEvents();
        void update();
        void render();

};
