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

class GameEngine {
	public:
		MouseRecorder* mouseRecorder;

		b2World* world;
		std::vector<Updateable*> updateables;
		std::vector<Renderable*> renderables;

		int tickFrequency;

		bool isMainWindowRunning = false;

		GameEngine(int tickFrequency) {
			this->mouseRecorder = new MouseRecorder(100, 10);

			b2Vec2* gravity = new b2Vec2(1.0f, 1.0f);
			this->world = new b2World(*gravity); 

			this->tickFrequency = tickFrequency;

			// b2BodyDef groundBodyDef;
			// groundBodyDef.position.Set(0.0f, 500.0f);
			// b2Body* groundBody = this->world->CreateBody(&groundBodyDef);
			// b2PolygonShape groundBox;
			// groundBox.SetAsBox(5000.0f, 1.0f);
			// groundBody->CreateFixture(&groundBox, 0.0f);
		};
		~GameEngine() {};

		void startMainWindow(const char* title, int xPos, int yPos, int width, int height, Uint32 sdlWindowFlags) {
			this->window = SdlScreenUtils::createWindow(title, xPos, yPos, width, height, sdlWindowFlags); 
			this->renderer = SdlScreenUtils::createRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			this->isMainWindowRunning = true;   
		};
		
		void tick() {
			auto unblockAt = std::chrono::steady_clock::now() + std::chrono::milliseconds(1 / this->tickFrequency);
			this->handleEvents();
			if (this->isMainWindowRunning) {
				this->update();
				this->render();
			}
			std::this_thread::sleep_until(unblockAt);
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
						this->cleanUp();
						this->isMainWindowRunning = false;
						break;
					case SDL_MOUSEBUTTONDOWN: 
						{                        
							SDL_Point mousePosition = this->mouseRecorder->getCurrentPosition();
							SDL_Rect* destinationArea = new SDL_Rect { mousePosition.x, mousePosition.y, 100, 100 };
							double rotation = 50;
							
							// BasicSpaceship* bs = new BasicSpaceship(this->renderer, destinationArea, rotation);
							// bs->spawn(*this->world);
							// this->updateables.push_back((Updateable*) bs);
							// this->renderables.push_back((Renderable*) bs);

							// Ball* ball = new Ball("assets/blue_ball.png", this->renderer, destinationArea, rotation);
							// ball->spawn(*this->world);
							// this->updateables.push_back((Updateable*) ball);
							// this->renderables.push_back((Renderable*) ball);
						} 
						break;
					case SDL_KEYUP:
						{
								b2Body* test = this->world->GetBodyList();
								std::cout << test->GetFixtureList() << std::endl;
						}
						break;
					default:
						break;
				}
			};
		}

		void update() {
			this->world->Step(1.0f / this->tickFrequency, 6, 2);
			std::function<void()> updateUpdateables = [=]() {
				for (Updateable* updateable : this->updateables) {
					updateable->onUpdate();
				}
			};
			updateUpdateables();
		};

		void render() {
			SDL_RenderClear(this->renderer);
			std::function<void()> renderRenderables = [=]() {
				for (Renderable* renderable : this->renderables) 
					renderable->onRender();
			};
			renderRenderables();
			SDL_RenderPresent(this->renderer);
		};
};
