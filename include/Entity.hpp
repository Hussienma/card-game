#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity{
private:
	SDL_Rect pos;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
	
public:
	Entity(SDL_Rect position, SDL_Rect frame, SDL_Texture* tex);
	SDL_Texture* getTexture();
	SDL_Rect getPos();
	SDL_Rect getCurrentFrame();
	void updatePos(int x, int y);
	void resize(float multiplier);
	void resize(int w, int h);
};
