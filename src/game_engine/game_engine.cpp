#include <SDL2/SDL_image.h>

#include <iostream>
#include <functional>
#include <utility>

#include "game_engine.hpp"
#include "game_engine_interfaces.hpp"
#include "../utils/sdl_utils.hpp"
#include "../utils/time_utils.hpp"
#include "mouse_utils.hpp"
#include "../models/ball.hpp"
#include "entity_factory.hpp"

//
// GAME ENGINE PUBLIC                                               
//

GameEngine::GameEngine() {
    this->mouseTelemetry = new MouseTelemetry(100, 10);
};

GameEngine::~GameEngine() { };

bool GameEngine::getIsMainWindowRunning() { 
    return this->isMainWindowRunning; 
};

void GameEngine::startMainWindow(const char* windowTitle, int windowXPos, int windowYPos, int windowWidth, int windowHeight, Uint32 sdlWindowFlags) {
    this->isMainWindowRunning = true;
    this->sdlWindow = SdlScreenUtils::createWindow(windowTitle, windowXPos, windowYPos, windowWidth, windowHeight, sdlWindowFlags); 
    this->sdlRenderer = SdlScreenUtils::createRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
};

void GameEngine::tick() {
    this->handleEvents();
    this->update();
    if (this->getIsMainWindowRunning())
        this->render();
    SDL_Delay(10);
};

void GameEngine::terminate() { 
    SDL_DestroyWindow(this->sdlWindow);
    SDL_DestroyRenderer(this->sdlRenderer);
    SDL_Quit();
};

//
// GAME ENGINE PRIVATE                                              
//

void GameEngine::handleEvents() {    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->isMainWindowRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    SDL_Point mousePosition = this->mouseTelemetry->getCurrentPosition();
                    SDL_Rect* destinationArea = new SDL_Rect { mousePosition.x, mousePosition.y, 100, 100 };
                    double* rotation = new double { 5 };
                    Ball* ball = EntityFactory::createBlueBall(this->sdlRenderer, destinationArea, rotation);
                    this->updateables.push_back((Updateable*) ball);
                    this->renderables.push_back((Renderable*) ball);
                }
                break;
            case SDL_KEYUP:
                std::cout << this->updateables.size() << std::endl;
                break;
            default:
                break;
        }
    }
};

void GameEngine::update() { 
    std::function<void()> updateUpdateables = [=]() {
        for (Updateable* updateable : this->updateables) 
            updateable->onUpdate(this->updateables);
    };
    updateUpdateables();
};

void GameEngine::render() { 
    SDL_RenderClear(this->sdlRenderer);
    std::function<void()> renderRenderables = [=]() {
        for (Renderable* renderable : this->renderables)
            renderable->onRender();
    };
    renderRenderables();
    SDL_RenderPresent(this->sdlRenderer);
};

