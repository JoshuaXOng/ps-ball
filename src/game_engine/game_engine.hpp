#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

#include <functional>
#include <vector>

#include "game_engine_interfaces.hpp"
#include "mouse_utils.hpp"
#include "state_repository.hpp"

class GameEngine {

    public:

        MouseTelemetry* mouseTelemetry;

        StateRepository* stateRepository;

        std::vector<Updateable*> updateables;
        std::vector<Renderable*> renderables;

        GameEngine();
        ~GameEngine();

        bool getIsMainWindowRunning();

        void startMainWindow(const char* windowTitle, int windowXPos, int windowYPos, int windowWidth, int windowHeight, Uint32 sdlWindowFlags);

        void tick();

        void terminate();

    private:

        bool isMainWindowRunning = false;

        SDL_Window* sdlWindow;
        SDL_Renderer* sdlRenderer;

        void handleEvents();
        void update();
        void render();

};
