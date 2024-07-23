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

	int getRefreshRate();

	void render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
	void clear();
	void display();
	void cleanUp();
};
