#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

#include <map>
#include <string>
#include <any>

class SdlScreenUtils {

    public: 

        static SDL_Window* createWindow(const char* title, int xPos, int yPos, int width, int height, Uint32 flags);

        static SDL_Renderer* createRenderer(SDL_Window *window, int index, Uint32 flags);

        static SDL_Texture* createTexture(const char* filePathToSurface, SDL_Renderer* renderer);

};