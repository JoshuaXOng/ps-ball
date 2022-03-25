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

class Wall : public Renderable, public Physicsable, public Updateable {
	public:
			Wall(SDL_Renderer* renderer, int id, std::string name, Position position, float angle, TwoDVector size, float scale)
			: Renderable(id, name, position, angle, size, scale), Physicsable(id, name, position, angle, size, scale),
			Updateable(id, name, position, angle, size, scale) {
				this->texture = SDLUtils::createTexture("assets/red_square.png", renderer);
				this->bodyDef = getBodyDef(position); 
				this->fixtureDef = this->getFixtureDef(size);
			};
			~Wall() {};
			
			void onRender() {};

			void onUpdate(SDL_Event event) {
				this->align();
				this->Renderable::position = this->Physicsable::position;
				this->Renderable::angle = this->Physicsable::angle;
			};

	private:
		b2BodyDef* getBodyDef(Position position) {
			b2BodyDef* bodyDef = new b2BodyDef();
			bodyDef->type = b2_staticBody;
			bodyDef->position.Set(position.first, position.second);
			return bodyDef;
		};

		b2Shape* getShape(TwoDVector size) {
			b2PolygonShape box;
      box.SetAsBox(size.first / 2, size.second / 2);
      b2PolygonShape* boxP = new b2PolygonShape(box);
      return boxP;
		};

		b2FixtureDef* getFixtureDef(TwoDVector size) {
			b2FixtureDef* fixtureDef = new b2FixtureDef();
			fixtureDef->shape = getShape(size);
			fixtureDef->density = 1.0f;
			fixtureDef->friction = 1.0f;
			return fixtureDef;
		};
};
