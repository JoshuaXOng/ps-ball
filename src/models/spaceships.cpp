#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include "spaceships.hpp"
#include "../utils/sdl_utils.hpp"

BasicSpaceship::BasicSpaceship(
    const std::vector<char*> filePathsToSurfaces, SDL_Renderer* renderer, 
    std::vector<SDL_Rect*> destinationAreas, std::vector<double> rotations
) : RenderableMulti(filePathsToSurfaces, renderer, destinationAreas, rotations), B2Entity(destinationArea, rotation) {
    this->density = 1.0f;
    this->friction = 0.3f;

    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(destinationArea->x, destinationArea->y);
    this->bodyDef = bodyDef;

    b2CircleShape circle;
    circle.m_radius = destinationArea->w / 2;
    circle.m_p.Set(0, 0);
    b2CircleShape* circleP = new b2CircleShape(circle);
    this->shape = circleP;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = this->shape;
    fixtureDef->density = this->density;
    fixtureDef->friction = this->friction;
    this->fixtureDef = fixtureDef;
};

BasicSpaceship::~BasicSpaceship() { };

// 
// BasicSpaceship class B2Entity virtual members implementations
//

void BasicSpaceship::onUpdate(std::vector<Updateable*> updateables) {
    this->B2Entity::onUpdate(updateables);
    this->Renderable::rotation = (this->body->GetAngle() / 3.14) * 180;
};
