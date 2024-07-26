#pragma once
#include<iostream>
#include<SDL2/SDL.h>

class RenderWindow{
	private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	public:
	RenderWindow(const char* title, int width, int height);
	SDL_Texture* loadTexture(const char* path);
	SDL_Texture* loadTextureFromSurface(SDL_Surface* surface);

	int getRefreshRate();

	void changeTextureColor(SDL_Texture* texture, Uint8 r, Uint8 g, Uint8 b);
	void render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
	void render(SDL_Texture* texture, SDL_Rect dst);
	void clear();
	void display();
	void destroyTexture(SDL_Texture* texture);
	void cleanUp();
};
