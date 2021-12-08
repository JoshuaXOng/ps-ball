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

    //
    // Hello Box2D
    //

    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    //
    // My application
    //

    // GameEngine* gameEngine = new GameEngine();
    // gameEngine->startMainWindow(
    //     MAIN_SDL_WINDOW_TITLE, 
    //     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    //     INITIAL_SDL_WINDOW_WIDTH, INITIAL_SDL_WINDOW_HEIGHT, 0
    // );

    // while (gameEngine->getIsMainWindowRunning()) 
    //     gameEngine->tick();

    // gameEngine->terminate();

    return GOOD_EXIT;

}


