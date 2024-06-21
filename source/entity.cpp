#include <SDL2/SDL.h>

#include "Entity.hpp"

Entity::Entity(int x, int y, SDL_Texture* tex) : texture(tex){
	pos.x = x;
	pos.y = y;
	pos.w = 64;
	pos.h = 53;
}

SDL_Texture* Entity::getTexture(){
	return texture;
}

SDL_Rect Entity::getPos(){ return pos; }

void Entity::updatePos(int x, int y){
	pos.x = x;
	pos.y = y;
}
