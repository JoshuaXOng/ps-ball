// #pragma once
// #include <SDL2/SDL.h>
// #include <box2d/box2d.h>
// #include <box2d/b2_world.h>
// #include <box2d/b2_body.h>
// #include <box2d/b2_polygon_shape.h>

// #include "model_interfaces.hpp"

// class BasicSpaceship : public B2Entity {

//     b2Body* body;

//     SDL_Renderer* renderer;
//     SDL_Texture* texture;
//     SDL_Rect* destinationArea;
//     double rotation;

//     BasicSpaceship(SDL_Renderer* renderer, SDL_Rect* destinationArea, double angleOfRotation);
//     ~BasicSpaceship();

//     void faceLocation(SDL_Point position);
    
//     void moveTopGlobal();
//     void moveRightGlobal();
//     void moveBotGlobal();
//     void moveLeftGlobal();

//     void moveTopRelative();
//     void moveRightRelative();
//     void moveBotRelative();
//     void moveLeftRelative();

//     //
//     // B2Entity abstract class declarations
//     //

//     float getDensity();
//     float getFriction();

//     b2BodyDef* getBodyDef();
//     b2Body* getBody();
//     b2PolygonShape* getShape();
//     b2FixtureDef* getFixtureDef();

//     void setBody(b2Body* body);

// };
