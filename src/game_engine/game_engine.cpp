#include <SDL2/SDL_image.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include <iostream>
#include <functional>
#include <utility>
#include <thread>
#include <chrono>
#include <future>

#include "game_engine.hpp"
#include "game_engine_interfaces.hpp"
#include "../utils/sdl_utils.hpp"
#include "../utils/time_utils.hpp"
#include "mouse_utils.hpp"
#include "../models/ball.hpp"
#include "../models/square.hpp"
#include "entity_factory.hpp"

//
// GameEngine public members
//

GameEngine::GameEngine(int tickFrequency) { //: world(gravity) {
    b2Vec2 gravity(5.0f, 10.0f);
    this->world = new b2World(gravity);
    this->isRunning = true;    
    this->tickFrequency = tickFrequency;
    this->mouseTelemetry = new MouseTelemetry(100, 10);
};

GameEngine::~GameEngine() { };

void GameEngine::startMainWindow(const char* title, int xPos, int yPos, int width, int height, Uint32 sdlWindowFlags) {
    this->isReadyToUpdate, this->isReadyToRender = true, true;
    this->window = SdlScreenUtils::createWindow(title, xPos, yPos, width, height, sdlWindowFlags); 
    this->renderer = SdlScreenUtils::createRenderer(window, -1, SDL_RENDERER_ACCELERATED);
};

void GameEngine::tick() {
    auto timeToUnblock = std::chrono::steady_clock::now() + std::chrono::milliseconds(this->tickFrequency);
    this->handleEvents();
    if (this->isReadyToUpdate)
        this->update();
    if (this->isReadyToRender)
        this->render();
    std::this_thread::sleep_until(timeToUnblock);
    
};

void GameEngine::cleanUp() { 
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
};

//
// GameEngine private members                                            
//

void GameEngine::handleEvents() {    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->isReadyToRender = false;
                this->isReadyToRender = false;
                this->isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN: 
                {                        
                    SDL_Point mousePosition = this->mouseTelemetry->getCurrentPosition();
                    SDL_Rect* destinationArea = new SDL_Rect { mousePosition.x, mousePosition.y, 2, 2 };
                    double* rotation = new double { 5 };
                    Square* square = new Square(this->renderer, destinationArea, rotation);
                    square->spawn(this->world);
                    // b2Vec2 test(100, 100);
                    // square->body->SetSleepingAllowed(false);
                    // square->body->SetLinearVelocity(test);
                    // this->updateables.push_back((Updateable*) ball);
                    this->renderables.push_back((Renderable*) square);
                }
                break;
            case SDL_KEYUP:
                std::cout << "Key up." << std::endl;
                break;
            default:
                break;
        }
    }
};

void GameEngine::update() { 
    // this->world.Step(1000 / this->tickFrequency, 6, 2);
    this->world->Step(1.0f / 60.0f, 6, 2);
    std::function<void()> updateUpdateables = [=]() {
        for (Updateable* updateable : this->updateables) 
            updateable->onUpdate(this->updateables);
    };
    updateUpdateables();
};

void GameEngine::render() { 
    SDL_RenderClear(this->renderer);
    std::function<void()> renderRenderables = [=]() {
        for (Renderable* renderable : this->renderables) 
            renderable->onRender();
        
    };
    renderRenderables();
    SDL_RenderPresent(this->renderer);
};

