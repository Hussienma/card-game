#pragma once
#include <SDL2/SDL.h>

class GraphicsComponent{
	private:
	SDL_Window* window;

	public:
	virtual void update(){}
};
