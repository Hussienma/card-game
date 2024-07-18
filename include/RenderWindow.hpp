#pragma once
#include "Entity.hpp"
#include<iostream>
#include<SDL2/SDL.h>
#include <vector>

class Card;

class RenderWindow{
	private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	public:
	RenderWindow(const char* title, int width, int height);
	SDL_Texture* loadTexture(const char* path);

	int getRefreshRate();

	void render(Entity& entity);
	void render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
	void renderPlayer(std::vector<Card*>& entites);
	void renderOpponent(Entity& card, int numberOfCards);
	void clear();
	void display();
	void cleanUp();
};
