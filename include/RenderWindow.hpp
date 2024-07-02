#pragma once
#include "Card.hpp"
#include "Entity.hpp"
#include<iostream>
#include<SDL2/SDL.h>
#include <vector>

class RenderWindow{
	private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	public:
	RenderWindow(const char* title, int width, int height);
	SDL_Texture* loadTexture(const char* path);

	int getRefreshRate();

	void render(Entity& entity);
	void render(std::vector<Card*>& entites);
	void clear();
	void display();
	void cleanUp();
};
