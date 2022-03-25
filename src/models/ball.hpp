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

class Ball : public Renderable, public Physicsable, public Updateable {
	public:
			Ball(int id, std::string name, SDL_Texture* texture, Position position, float angle, float radius, float scale)
			 	: Renderable(id, name, position, angle, { 2*radius, 2*radius }, scale), Physicsable(id, name, position, angle, { 2*radius, 2*radius }, scale),
				Updateable(id, name, position, angle, { 2*radius, 2*radius }, scale) {
				this->texture = texture;
				this->bodyDef = getBodyDef(position); 
				this->fixtureDef = this->getBallFixtureDef(radius);
			};
			~Ball() {};
			
			void onRender() {};
			void onUpdate() {};

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

		b2FixtureDef* getBallFixtureDef(float radius) {
			b2FixtureDef* fixtureDef = new b2FixtureDef();
			fixtureDef->shape = getShape(radius);
			fixtureDef->density = 1.0f;
			fixtureDef->friction = 0.3f;
			return fixtureDef;
		};
};
