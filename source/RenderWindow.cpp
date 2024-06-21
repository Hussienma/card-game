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
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
	
}

SDL_Texture* RenderWindow::loadTexture(const char* path){
	SDL_Texture* texture = IMG_LoadTexture(renderer, path);
	if(texture == NULL)
		std::cerr<<"Error loading texture at '"<<path<<"': "<<SDL_GetError()<<std::endl;
	return texture;
}

void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity){
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 64;
	src.h = 53;

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
