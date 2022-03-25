#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <map>
#include <string>
#include <any>
#include "../constants.hpp"

class SDLUtils {
	public: 
		static SDL_Window* createWindow(const char* title, int xPos, int yPos, int width, int height, Uint32 flags) {
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) throw SDL_GetError();
			SDL_Window* window = SDL_CreateWindow(title, xPos, yPos, width, height, flags); 
			if (!window) throw SDL_GetError();
			return window;
		};

		static SDL_Renderer* createRenderer(SDL_Window *window, int index, Uint32 flags) {
			SDL_Renderer* renderer = SDL_CreateRenderer(window, index, flags);
			if(!renderer) throw SDL_GetError();
			return renderer;
		};

		static SDL_Texture* createTexture(const char* filePathToSurface, SDL_Renderer* renderer) {
			SDL_Surface* surface = IMG_Load(filePathToSurface);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);    
			return texture;
		};
};