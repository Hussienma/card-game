#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "RenderWindow.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Utils.hpp"

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		std::cerr<<"Unable to initialize SDL" <<SDL_GetError()<<std::endl;
		exit(1);
	}
	
	RenderWindow window("Game window", 640, 480);

	SDL_Event event;
	bool gameRunning = true;

	SDL_Rect pos;
	pos.x = 0;
	pos.y = 368;
	pos.w = 96;
	pos.h = 128;

	Player player1("p1", pos.y);
	Player player2("p2", pos.y);
	std::vector<Player*> players;
	players.push_back(&player1);
	players.push_back(&player2);

	SDL_Texture* cardsTexture = window.loadTexture("./gfx/Cards.png");
	SDL_Texture* colorWheelTexture = window.loadTexture("./gfx/Color Selection Wheel.png");

	SDL_Rect colorWheelPos;
	colorWheelPos.x = 0;
	colorWheelPos.y = 0;
	colorWheelPos.w = 256;
	colorWheelPos.h = 256;
	Entity colorWheel(colorWheelPos, colorWheelPos, colorWheelTexture);
	Game game(players, cardsTexture);
	Card* cardOnField = nullptr;

	std::vector<Card*> playerCards = player1.getCards();

	const float timeStep = 0.01f;

	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while(gameRunning){
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;

		gameState state = game.getGameState();

		while(accumulator >= timeStep){
		while(SDL_PollEvent(&event))
			switch(event.type){
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
			case SDL_QUIT:
				gameRunning = false;
			}

				for(Card* b : playerCards){
					b->animate();
				}
				accumulator -= timeStep;
		}


		window.clear();
		if(cardOnField != nullptr)
			window.render(*cardOnField);

		if(state == PICK_COLOR)
			window.render(colorWheel);
		window.render(playerCards);
		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if(frameTicks < 1000/window.getRefreshRate())
			SDL_Delay(1000/window.getRefreshRate() - frameTicks);
	}
	
	window.cleanUp();
	SDL_Quit();
	return 0;
}
