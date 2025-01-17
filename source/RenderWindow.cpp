#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height){
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 1);
}

SDL_Texture* RenderWindow::loadTexture(const char* path){
	SDL_Texture* texture = IMG_LoadTexture(renderer, path);
	if(texture == NULL)
		std::cerr<<"Error loading texture at '"<<path<<"': "<<SDL_GetError()<<std::endl;
	return texture;
}

SDL_Texture* RenderWindow::loadTextureFromSurface(SDL_Surface* surface){
	return SDL_CreateTextureFromSurface(renderer, surface);
}

int RenderWindow::getRefreshRate(){
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	
	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::changeTextureColor(SDL_Texture* texture, Uint8 r, Uint8 g, Uint8 b){
	SDL_SetTextureColorMod(texture, r, g, b);
}

void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst){
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::render(SDL_Texture* texture, SDL_Rect dst){
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void RenderWindow::display(){ SDL_RenderPresent(renderer); }

void RenderWindow::destroyTexture(SDL_Texture* texture){
	SDL_DestroyTexture(texture);
}

void RenderWindow::cleanUp(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
