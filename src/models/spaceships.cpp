// #include <box2d/box2d.h>
// #include <box2d/b2_world.h>
// #include <box2d/b2_body.h>
// #include <box2d/b2_polygon_shape.h>

// #include "spaceships.hpp"
// #include "../utils/sdl_utils.hpp"

// BasicSpaceship::BasicSpaceship(SDL_Renderer* renderer, SDL_Rect* destinationArea, double rotation) {
//     this->renderer = renderer;
//     this->texture = SdlScreenUtils::createTexture("assets/red_square.png", this->renderer);
//     this->destinationArea = destinationArea;
//     this->rotation = rotation;
// };

// // 
// // BasicSpaceship class B2Entity virtual member implementations
// //

// float BasicSpaceship::getDensity() {
//     return 1.0f;
// };

// float BasicSpaceship::getFriction() {
//     return 0.5f;
// };

// b2BodyDef* BasicSpaceship::getBodyDef() {
//     b2BodyDef* bodyDef = new b2BodyDef();
//     bodyDef->type = b2_dynamicBody;
//     bodyDef->position.Set(this->destinationArea->x, this->destinationArea->y);
//     return bodyDef;
// };

// b2Body* BasicSpaceship::getBody() { return this->body; };

// b2PolygonShape* BasicSpaceship::getShape() { 
//     b2PolygonShape shape;
//     shape.SetAsBox(destinationArea->w / 2, destinationArea->h / 2);
//     b2PolygonShape* shapeP = new b2PolygonShape(shape);
//     return shapeP;
// };

// b2FixtureDef* BasicSpaceship::getFixtureDef() {
//     b2FixtureDef* fixtureDef = new b2FixtureDef();
//     fixtureDef->shape = this->getShape();
//     fixtureDef->density = this->getDensity();
//     fixtureDef->friction = this->getFriction();
//     return fixtureDef;
// };

// void BasicSpaceship::setBody(b2Body* body) { this->body = body; };

