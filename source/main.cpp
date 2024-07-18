#include <iostream>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>

#include "RenderWindow.hpp"
#include "Game.hpp"
#include "Utils.hpp"

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		std::cerr<<"Unable to initialize SDL" <<SDL_GetError()<<std::endl;
		exit(1);
	}
	
	RenderWindow window("Game window", 640, 480);

	Game game(window);

	const float timeStep = 0.01f;

	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while(game.getGameState() != QUIT){
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;

		while(accumulator >= timeStep){
			window.clear();
			game.update();
			accumulator -= timeStep;
		}

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if(frameTicks < 1000/window.getRefreshRate())
			SDL_Delay(1000/window.getRefreshRate() - frameTicks);
	}
	
	window.cleanUp();
	SDL_Quit();
	return 0;
}
