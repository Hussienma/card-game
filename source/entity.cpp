#include <SDL2/SDL.h>

#include "Entity.hpp"

Entity::Entity(SDL_Rect pos, SDL_Rect currentFrame, SDL_Texture* tex) : texture(tex){
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->pos.w = pos.w;
	this->pos.h = pos.h;

	this->currentFrame = currentFrame;
	this->collider = pos;
}

SDL_Texture* Entity::getTexture(){
	return texture;
}

SDL_Rect Entity::getPos(){ return pos; }

SDL_Rect Entity::getCollider(){ return collider; }

void Entity::setCollider(int w, int h){
	collider.w = w;
	collider.h = h;
}

void Entity::updatePos(int x, int y){
	pos.x = x;
	pos.y = y;
	collider.x = x;
	collider.y = y;
}

void Entity::resize(float multiplier){
	int w = pos.w * multiplier;
	int h = pos.h * multiplier;
	pos.w = w;
	pos.h = h;
	collider.w = collider.w * multiplier;
	collider.h = collider.h * multiplier;
}

void Entity::resize(int w, int h){
	pos.w = w;
	pos.h = h;
	setCollider(w, h);
}

SDL_Rect Entity::getCurrentFrame(){ return currentFrame; }
