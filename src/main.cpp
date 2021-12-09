#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <any>

#include "game_engine/game_engine.hpp"
#include "utils/sdl_utils.hpp"
#include "application_constants.hpp"
#include "utils/math_utils.hpp"
#include "utils/keyboard_utils.hpp"
#include "utils/time_utils.hpp"

int main(int argc, char** argv) {

    GameEngine* gameEngine = new GameEngine(10);
    gameEngine->startMainWindow(
        INITIAL_MAIN_WINDOW_TITLE, 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, 0
    );

    while (gameEngine->isRunning)
        gameEngine->tick();

    gameEngine->cleanUp();

    return EXIT_SUCCESS;

};

//
// Hello Box2D ("tutorial")
//

void helloBox2D() {

    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    for (int32 i = 0; i < 60; ++i) {
        world.Step(1.0f / 60.0f, 6, 2);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }

};





