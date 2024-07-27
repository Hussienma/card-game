#include "Controller.hpp"
#include "Game.hpp"

SDL_Event* Controller::event;

SDL_Event* Controller::handleInput(Game& game){
	while(SDL_PollEvent(event)){
		switch(event->type){
			case SDL_QUIT:
				game.state = QUIT;
				break;
			default:
				return event;
		}
	}
	return event;
}
