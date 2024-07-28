#include <iostream>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>

#include "Constants.h"
#include "Controller.hpp"
#include "GameObject.hpp"
#include "Index.hpp"
#include "RenderWindow.hpp"
#include "Game.hpp"
#include "UI.hpp"
#include "Utils.hpp"

ApplicationState state = MAIN_MENU;
PlayButton playButton;
QuitButton quitButton;

void update(RenderWindow& window, Game& game){
	Controller::handleInput(game);
	playButton.update(game);
	quitButton.update(game);
	
	playButton.render();
	quitButton.render();
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
	RenderWindow window("Game window", WINDOW_WIDTH, WINDOW_HEIGHT);

	Game game(window);

	SDL_Texture* background = window.loadTexture("./gfx/Background Pattern.png");
	SDL_Texture* logoTexture = window.loadTexture("./gfx/Logo.png");
	UI logo({CENTER_HOR, CENTER_VER-70, WINDOW_WIDTH, static_cast<int>(0.67*WINDOW_WIDTH)}, new GraphicsComponent(&window, new Sprite(logoTexture, {0, 0, 600, 400})));
	logo.visible = true;
	logo.hoverAnimation = new Animation(20);

	SDL_Texture* shadowTexture = window.loadTexture("./gfx/Shadow.png");
	SDL_Texture* buttonTexture1 = window.loadTexture("./gfx/Button.png");
	SDL_Texture* buttonTexture2 = window.loadTexture("./gfx/Button.png");
	SDL_Color white = {255, 255, 255};
	SDL_Color btnPrimary = { 102, 123, 198 };
	SDL_Color btnSecondary = { 180, 70, 30 };
	playButton = PlayButton(state, new Text(&window, white, "Play", "Sans", 24, CENTER_HOR-80, CENTER_VER+WINDOW_HEIGHT/4), btnPrimary, {CENTER_HOR-80, CENTER_VER+WINDOW_HEIGHT/4, 120, 50}, new GraphicsComponent(&window, new Sprite(buttonTexture1, {0, 0, 200, 100}, shadowTexture), true), new UIInputComponent());
	quitButton = QuitButton(new Text(&window, white, "Quit", "Sans", 24, CENTER_HOR+80, CENTER_VER+WINDOW_HEIGHT/4), btnSecondary, {CENTER_HOR+80, CENTER_VER+WINDOW_HEIGHT/4, 120, 50}, new GraphicsComponent(&window, new Sprite(buttonTexture2, {0, 0, 200, 100}, shadowTexture), true), new UIInputComponent());

	playButton.visible = true;
	quitButton.visible = true;
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
			window.render(background, {0,0,WINDOW_WIDTH, WINDOW_HEIGHT}, {0,0,WINDOW_WIDTH, WINDOW_HEIGHT});
			switch(state){
				case IN_GAME:
					game.update();
					break;
				case MAIN_MENU:
					logo.animate();
					logo.render();
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
