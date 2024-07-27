#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include "Game.hpp"

class Controller {
	private:
	static SDL_Event* event;
	
	public:
	Controller(){
		event = new SDL_Event();
	}

	static SDL_Event* handleInput(Game& game);
};
