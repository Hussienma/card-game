#include <SDL2/SDL.h>

#include "Entity.hpp"

Entity::Entity(SDL_Rect pos, SDL_Rect currentFrame, SDL_Texture* tex) : texture(tex){
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->pos.w = pos.w;
	this->pos.h = pos.h;

	this->currentFrame = currentFrame;
}

SDL_Texture* Entity::getTexture(){
	return texture;
}

SDL_Rect Entity::getPos(){ return pos; }

void Entity::updatePos(int x, int y){
	pos.x = x;
	pos.y = y;
}

void Entity::resize(float multiplier){
	int w = pos.w * multiplier;
	int h = pos.h * multiplier;
	pos.w = w;
	pos.h = h;
}

void Entity::resize(int w, int h){
	pos.w = w;
	pos.h = h;
}

SDL_Rect Entity::getCurrentFrame(){ return currentFrame; }
