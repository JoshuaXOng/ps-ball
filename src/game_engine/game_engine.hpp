#pragma once
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <stdio.h>
#include <functional>
#include <vector>
#include "mouse_recorder.hpp"
#include "./entities/renderable.hpp"
#include "./entities/updateable.hpp"
#include "./math_utils.hpp"
#include "./sdl_utils.hpp"
#include "./time_utils.hpp"
#include "../models/ball.hpp"

class GameEngine {
	public:
		MouseRecorder* mouseRecorder;

		b2World* world;
		std::vector<Updateable*> updateables;
		std::vector<Renderable*> renderables;

		int tickFrequency;

		bool isMainWindowRunning = false;

		GameEngine(int tickFrequency) {
			this->mouseRecorder = new MouseRecorder();

			b2Vec2* gravity = new b2Vec2(0.0f, 1.0f);
			this->world = new b2World(*gravity); 

			this->tickFrequency = tickFrequency;
		};
		~GameEngine() {};

		void startMainWindow(const char* title, int xPos, int yPos, int width, int height, Uint32 sdlWindowFlags) {
			this->window = SDLUtils::createWindow(title, xPos, yPos, width, height, sdlWindowFlags); 
			this->renderer = SDLUtils::createRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			this->isMainWindowRunning = true;
		};

		void addInitialEntities() {
			// b2BodyDef groundBodyDef;
			// groundBodyDef.position.Set(0.0f, 500.0f);
			// b2Body* groundBody = this->world->CreateBody(&groundBodyDef);
			// b2PolygonShape groundBox;
			// groundBox.SetAsBox(5000.0f, 1.0f);
			// groundBody->CreateFixture(&groundBox, 0.0f);

			Ball* ball = new Ball(this->renderer, 0, "Common Ball", { 5, 6 }, 0, 10, 1);
		
			b2Body* body = this->world->CreateBody(ball->bodyDef);
			ball->body = body;
			body->CreateFixture(ball->fixtureDef);
		
			this->updateables.push_back((Updateable*) ball);
			this->renderables.push_back((Renderable*) ball);
		};
		
		void tick() {
			TimeUtils::setTimeout(1 / this->tickFrequency, [=]() {
				this->handleEvents();
				if (this->isMainWindowRunning) {
					this->update();
					this->render();
				}
			});
		};

		void cleanUp() {
			SDL_DestroyWindow(this->window);
			SDL_DestroyRenderer(this->renderer);
			SDL_Quit();
		};

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		void handleEvents() {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT:
						this->isMainWindowRunning = false;
						break;
					case SDL_MOUSEBUTTONDOWN: 
						{    
							std::cout << "Mouse button down event fired!" << std::endl;
							this->addInitialEntities();
						} 
						break;
					case SDL_KEYUP:
						{
							std::cout << "Key-up event fired!" << std::endl;
						}
						break;
					default:
						break;
				}
			};
		}
		
		void update() {
			this->world->Step(1.0f / this->tickFrequency, 6, 2);
			for (Updateable* updateable : this->updateables) {
				updateable->onUpdate();
			}
		};

		void render() {
			SDL_RenderClear(this->renderer);
			for (Renderable* renderable : this->renderables) {
				if (renderable->texture) {
					SDL_Rect destination = {
						renderable->position.first, renderable->position.second,
						renderable->size.first, renderable->size.second,
					};
					SDL_RenderCopyEx( 
						this->renderer, renderable->texture,
						NULL, &destination,
						renderable->angle, NULL, SDL_FLIP_NONE
					);
					renderable->onRender();
				} else {
					std::cout << "GameEngine tried to render Renderable w/o a texture." << std::endl;
				}
			}
			SDL_RenderPresent(this->renderer);
		};
};
