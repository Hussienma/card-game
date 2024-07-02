#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

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

void RenderWindow::render(Entity& entity){
	SDL_Rect src;
	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = entity.getPos().x;
	dst.y = entity.getPos().y;
	dst.w = entity.getPos().w;
	dst.h = entity.getPos().h;

	SDL_Texture* texture = entity.getTexture();

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::render(std::vector<Card*>& entites){
	for(Entity* entity: entites)
		render(*entity);
}

void RenderWindow::display(){ SDL_RenderPresent(renderer); }

void RenderWindow::cleanUp(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
