#include <iostream>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>

#include "Controller.hpp"
#include "Index.hpp"
#include "RenderWindow.hpp"
#include "Game.hpp"
#include "UI.hpp"
#include "Utils.hpp"

ApplicationState state = MAIN_MENU;
PlayButton playButton;

void update(RenderWindow& window, Game& game){
	playButton.update(game);
	
	playButton.visible = true;
	playButton.render();
}

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		std::cerr<<"Unable to initialize SDL" <<SDL_GetError()<<std::endl;
		exit(1);
	}

	if(TTF_Init() == -1){
		std::cerr<<"Failed to initialize TTF!\n";
		exit(1);
	}
	
	Controller controller;
	RenderWindow window("Game window", 640, 480);

	Game game(window);

	SDL_Texture* buttonTexture = window.loadTexture("./gfx/Button.png");
	playButton = PlayButton(state, new Text(&window, {255,255,255}, "Play", "Sans", 24, 320, 240), {25, 0, 0}, {320, 240, 120, 50}, new GraphicsComponent(&window, new Sprite(buttonTexture, {0, 0, 200, 100})), new UIInputComponent());

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
			switch(state){
				case IN_GAME:
					game.update();
					break;
				case MAIN_MENU:
					update(window, game);
					break;
			}
			window.display();
			accumulator -= timeStep;
		}


		int frameTicks = SDL_GetTicks() - startTicks;

		if(frameTicks < 1000/window.getRefreshRate())
			SDL_Delay(1000/window.getRefreshRate() - frameTicks);
	}
	
	window.cleanUp();
	SDL_Quit();
	return 0;
}
