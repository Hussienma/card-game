#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"

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

int RenderWindow::getRefreshRate(){
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	
	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* texture, SDL_Rect frame, SDL_Rect pos){
	SDL_Rect src;
	src.x = frame.x;
	src.y = frame.y;
	src.w = frame.w;
	src.h = frame.h;

	SDL_Rect dst;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = pos.w;
	dst.h = pos.h;
	
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::display(){ SDL_RenderPresent(renderer); }

void RenderWindow::cleanUp(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
