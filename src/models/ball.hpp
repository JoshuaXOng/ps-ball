#pragma once
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <string>
#include "../game_engine/entities/renderable.hpp"
#include "../game_engine/entities/physicsable.hpp"
#include "../game_engine/entities/updateable.hpp"
#include "../game_engine/sdl_utils.hpp"
#include "../game_engine/types.hpp"
#include "../game_engine/mouse_recorder.hpp"

auto test = new MouseRecorder();

class Ball : public Renderable, public Physicsable, public Updateable {
	public:
			Ball(SDL_Renderer* renderer, int id, std::string name, Position position, float angle, float radius, float scale)
			: Renderable(id, name, position, angle, { 2*radius, 2*radius }, scale), Physicsable(id, name, position, angle, { 2*radius, 2*radius }, scale),
			Updateable(id, name, position, angle, { 2*radius, 2*radius }, scale) {
				this->texture = SDLUtils::createTexture("assets/blue_ball.png", renderer);
				this->bodyDef = getBodyDef(position); 
				this->fixtureDef = this->getFixtureDef(radius);
			};
			~Ball() {};
			
			void onRender() {};

			void onUpdate(SDL_Event event) {
				// if (event.type == 771) {
				// if (event.type == SDL_MOUSEBUTTONDOWN) { 
				// 	// std::cout << "reaches?" << std::endl;
				// 	this->body->ApplyForce({ 1000, 1000 }, { 0, 0 }, true); 
				// }
				int x = test->getCurrentPosition().x - this->Physicsable::position.first;
				int y = test->getCurrentPosition().y - this->Physicsable::position.second;
				this->body->ApplyForce({ x, y }, { 0, 0 }, true);

				this->align();
				this->Renderable::position = this->Physicsable::position;
				this->Renderable::angle = this->Physicsable::angle;
			};

	private:
		b2BodyDef* getBodyDef(Position position) {
			b2BodyDef* bodyDef = new b2BodyDef();
			bodyDef->type = b2_dynamicBody;
			bodyDef->position.Set(position.first, position.second);
			return bodyDef;
		};

		b2Shape* getShape(float radius) {
			b2CircleShape circle;
			circle.m_radius = radius;
			b2CircleShape* circleP = new b2CircleShape(circle);
			return circleP;
		};

		b2FixtureDef* getFixtureDef(float radius) {
			b2FixtureDef* fixtureDef = new b2FixtureDef();
			fixtureDef->shape = getShape(radius);
			fixtureDef->density = 1.0f;
			fixtureDef->friction = 1.0f;
			return fixtureDef;
		};
};
