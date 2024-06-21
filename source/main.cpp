#include "RenderWindow.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "Entity.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "Game.hpp"

using namespace std;

int main(){
	cout<<"Hello world\n";
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		cerr<<"Unable to initialize SDL" <<SDL_GetError()<<endl;
		exit(1);
	}
	
	RenderWindow window("Game window", 640, 480);

	SDL_Event event;
	bool gameRunning = true;

	int dx = 3;
	int dy = -2;
	Uint32 lastFrameTime = 0, currentFrameTime;
		
	SDL_Texture* ballTexture = window.loadTexture("./gfx/ball_resized.png");
	if(ballTexture == NULL){
		cerr<<SDL_GetError()<<endl;
		exit(1);
	}

	Card ball(RED, 4, ballTexture);
	Card ball2(YELLOW, 0, ballTexture);

	vector<Card> deck;
	for(int i=0; i<=10; ++i)
		deck.push_back(Card(RED, i, ballTexture));
	Player player1("p1");
	Game game(&player1, deck);

	for(int i=0; i<=10; i++)
		game.draw(&player1);

	game.play(&player1, &deck[2]);
	game.play(&player1, &deck[2]);
	game.play(&player1, &deck[9]);
	vector<Card*> cards = {&ball, &ball2};

	player1.sortCards();
	std::vector<Card*> playerCards = player1.getCards();
	while(gameRunning){
		while(SDL_PollEvent(&event))
			switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
				for(Card* b : playerCards){
					if(event.button.x >= b->getPos().x && event.button.x <= b->getPos().x + b->getPos().w && event.button.y >= b->getPos().y && event.button.y <= b->getPos().y + b->getPos().h){
						cout<<"Selected "<<b->getValue()<<" of "<<b->getColorString()<<" card\n";
						break;
					}
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
		window.render(playerCards);
		window.display();
	}
	
	SDL_Quit();
	return 0;
}
