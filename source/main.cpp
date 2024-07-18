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
			game.update();
			/*
			case SDL_MOUSEBUTTONDOWN:
				if(state == TURNS){
					for(Card* b : playerCards){
						if(b->checkCollision(event.button.x, event.button.y) && game.getCurrentPlayerTurn() == &player1){
							std::cout<<"Selected "<<b->getValue()<<" of "<<b->getColorString()<<" card\n";
							if(b->getColor() == WILD)
								game.setState(PICK_COLOR);
							bool valid = game.play(b);
							if(valid){
								b->updatePos(320-b->getPos().w/4, 240-b->getPos().h/4);
								cardOnField = b;
								b->resize(0.5f);
								player1.sortCards();
								playerCards = player1.getCards();
							}

							break;
						}
					}
				}
				else if(state == PICK_COLOR){
					if(colorWheel.checkCollision(event.button.x, event.button.y)){
						ChangeColorCard* c = (ChangeColorCard*)cardOnField;
						c->setColor(YELLOW);
						std::cout<<"Clicked the wheel. Card on field is: "<<c->getColorString()<<std::endl;
						game.setState(TURNS);
					}
				}

				break;
			case SDL_MOUSEMOTION:
				if(state == TURNS){
					for(Card* b : playerCards){
						if(b->checkCollision(event.button.x, event.button.y)){
							b->setHover(true);
						}
						else {
							b->setHover(false);
						}
					}
				}

				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_SPACE){
					game.drawAndGoNext();
					player1.sortCards();
					playerCards = player1.getCards();
				}

				break;
			*/
				accumulator -= timeStep;
		}

		window.clear();
		game.render();
		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if(frameTicks < 1000/window.getRefreshRate())
			SDL_Delay(1000/window.getRefreshRate() - frameTicks);
	}
	
	window.cleanUp();
	SDL_Quit();
	return 0;
}
