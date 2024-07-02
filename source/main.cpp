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

using namespace std;

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		cerr<<"Unable to initialize SDL" <<SDL_GetError()<<endl;
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

	/*
	SDL_Rect frame;
	frame.x = 0;
	frame.y = 0;
	frame.w = 192;
	frame.h = 256;

	// TODO: Refactor this and put it in the game class
	vector<Card> deck;
	for(int i=0; i<10; ++i){
		for(int j=0; j<4; j++){
			std::string color;
			Color c;
			switch(j){
				case 0:
					c = RED;
					color = "Red"; 
					break;
				case 1: 
					c = GREEN;
					color = "Green";
					break;
				case 2:
					c = YELLOW;
					color = "Yellow";
					break;
				case 3: 
					c = BLUE;
					color = "Blue";
					break;
				default:
					c = RED;
					color = "Red";
			}

			// TODO: make all the cards one big texture and make sprites from it
			std::string path = "./gfx/" + color + "_" + std::to_string(i) + ".png";
			SDL_Texture* cardTexture = window.loadTexture(path.c_str());

			deck.push_back(Card(c, i, pos, frame, cardTexture));
		}
	}
	*/

	Player player1("p1", pos.y);
	Player player2("p2", pos.y);
	std::vector<Player*> players;
	players.push_back(&player1);
	players.push_back(&player2);

	SDL_Texture* cardsTexture = window.loadTexture("./gfx/Cards.png");
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

		while(accumulator >= timeStep){
		while(SDL_PollEvent(&event))
			switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
				for(Card* b : playerCards){
					if(b->checkCollision(event.button.x, event.button.y)){
						cout<<"Selected "<<b->getValue()<<" of "<<b->getColorString()<<" card\n";

						bool valid = game.play(&player1, b);
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
				break;
			case SDL_MOUSEMOTION:
				for(Card* b : playerCards){
					SDL_Rect collider = b->getCollider();
					if(b->checkCollision(event.button.x, event.button.y)){
						b->setHover(true);
					}
					else {
						b->setHover(false);
					}
				}

				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_SPACE){
					game.draw(&player1);
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
