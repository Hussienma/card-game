#include "RenderWindow.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "Card.hpp"
#include "Player.hpp"
#include "Game.hpp"

using namespace std;

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		cerr<<"Unable to initialize SDL" <<SDL_GetError()<<endl;
		exit(1);
	}
	
	RenderWindow window("Game window", 640, 480);

	SDL_Event event;
	bool gameRunning = true;

	Uint32 lastFrameTime = 0, currentFrameTime;
		
	SDL_Rect pos;
	pos.x = 0;
	pos.y = 368;
	pos.w = 96;
	pos.h = 128;

	SDL_Rect frame;
	frame.x = 0;
	frame.y = 0;
	frame.w = 192;
	frame.h = 256;
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
			std::string path = "./gfx/" + color + "_" + std::to_string(i) + ".png";
			SDL_Texture* cardTexture = window.loadTexture(path.c_str());

			deck.push_back(Card(c, i, pos, frame, cardTexture));
		}
	}
	for(Card card: deck)
		std::cout<<card.getValue()<<card.getColorString()<<std::endl;
	Player player1("p1", pos.y);
	Game game(&player1, deck);
	Card* cardOnField;

	int x,y;
	for(int i=0; i<=10; i++)
		game.draw(&player1);

	player1.sortCards();
	std::vector<Card*> playerCards = player1.getCards();
	while(gameRunning){
		while(SDL_PollEvent(&event))
			switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
				for(Card* b : playerCards){
					if(event.button.x >= b->getPos().x && event.button.x <= b->getPos().x + b->getPos().w/1.5 && event.button.y >= b->getPos().y && event.button.y <= b->getPos().y + b->getPos().h){
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
					if(event.button.x >= b->getPos().x && event.button.x <= b->getPos().x + b->getPos().w/1.5 && event.button.y >= b->getPos().y && event.button.y <= b->getPos().y + b->getPos().h){
							b->hover();
					}
					else {
						b->unhover();
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

		currentFrameTime = SDL_GetTicks();
		if(currentFrameTime - lastFrameTime > 16){
			lastFrameTime = currentFrameTime;
		}


		window.clear();
		if(cardOnField != NULL)
			window.render(*cardOnField);
		window.render(playerCards);
		window.display();
	}
	
	SDL_Quit();
	return 0;
}
