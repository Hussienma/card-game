#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity{
private:
SDL_Rect pos;
SDL_Texture* texture;

public:
Entity(int x, int y, SDL_Texture* tex);
SDL_Texture* getTexture();
SDL_Rect getPos();
void updatePos(int x, int y);
};
