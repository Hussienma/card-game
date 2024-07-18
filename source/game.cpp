#include "Game.hpp"
#include "Constants.h"
#include "GameObject.hpp"
#include "LinkedList.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <string>

Game::Game(RenderWindow& window): window(&window), state(START){
	cardsTexture = window.loadTexture("./gfx/Cards.png");
	initializeCards();
	player = new Player("p1", new InputComponent());
	opponent = new Player("p2", new InputComponent());
	for(Uint16 i=0; i<cards.size(); i++){
		deck.push_back(&cards[i]);
	}

	turns.insertPlayer(*player);
	turns.insertPlayer(*opponent);

	for(int i=0; i<20; ++i){
		draw();
		turns.goNext();
	}
	player->sortCards();

	state = TURNS;
}

void Game::render(){
	for(Card card: cards){
		card.render();
	}
}


// TODO: We might wanna move the input handling inside the InputComponent rather than here
void Game::update(){
	Player* player = turns.getCurrentTurn();
	player->update(*this);
}

void Game::initializeCards(){
	Color color;
	SDL_Rect frame;
	frame.x = 0;
	frame.w = 192;
	frame.h = 256;

	for(int i=0; i<4; ++i){
		switch(i){
			case 0: color = BLUE; break;
			case 1: color = GREEN; break;
			case 2: color = RED; break;
			case 3: color = YELLOW; break;
		}
		frame.y = i*256;
		frame.x = 0;

		cards.push_back(Card(NUMBER, color, 0, new GraphicsComponent(window, new Sprite(cardsTexture, frame))));

		frame.x = 192;
		for(int j=1; j<10; ++j){
			Card card = Card(NUMBER, color, j, new GraphicsComponent(window, new Sprite(cardsTexture, frame)));
			cards.push_back(card);
			cards.push_back(card);
			frame.x += 192;
		}

		for(int j=0; j<2; ++j){
			cards.push_back(
				Card(REVERSE, color, 10, new GraphicsComponent(window, new Sprite(cardsTexture, frame)))
			);
		}

		frame.x += 192;
		for(int j=0; j<2; ++j){
			cards.push_back(
				Card(DRAW_2, color, 11, new GraphicsComponent(window, new Sprite(cardsTexture, frame)))
			);
		}

		frame.x += 192;
		for(int j=0; j<2; ++j){
			cards.push_back(
				Card(SKIP, color, 12, new GraphicsComponent(window, new Sprite(cardsTexture, frame)))
			);
		}
	}

	// WILD Change Color
	frame.x += 192;
	frame.y = 0;
	for(int i=0; i<4; ++i)
		cards.push_back(
			Card(WILD, color, 13, new GraphicsComponent(window, new Sprite(cardsTexture, frame)))
		);

	// WILD +4 cards
	frame.y = 256;
	for(int i=0; i<4; ++i)
		cards.push_back(
			Card(DRAW_4, color, 14, new GraphicsComponent(window, new Sprite(cardsTexture, frame)))
		);
}

void Game::draw(){
	Player* player = turns.getCurrentTurn();
	if(deck.size() == 0){
		std::cout<<"Refilling deck!\n";
		refillDeck();
		if(deck.size() == 0){
			std::cerr<<"Deck & field are empty!\n";
			return;
		}
	}
	
	std::srand(time(NULL));

	int pos = rand();
	pos %= deck.size();

	Card* card = deck[pos];
	deck.erase(deck.begin()+pos);
	player->draw(card);
}

void Game::drawAndGoNext(){
	draw();
	turns.goNext();
}

bool Game::play(Card* card){
	// TODO: Refactor this whole mess DONE??
	/*
	if(field.size() > 0 && field.back()->getColor() == WILD){
		ChangeColorCard c = *(ChangeColorCard*)field.back();
		if(c.getColor() != card->getColor()){
			std::cerr<<"Invalid play: current color is: "<<c.getColor()<<std::endl;
			return false;
		}
	}
	*/

	// WARNING: Playing with fire here
	Card* cardOnField = nullptr;
	if(field.size() > 0)
		cardOnField = field.back(); 

	if(cardOnField != nullptr 
		&& card->getValue() < 13 
		&& cardOnField->getColor() != card->getColor()
		&& cardOnField->getValue() != card->getValue()){
		std::cerr<<"Invalid play: card isn't the same color or number.\n";
		return false;
	}

	Player* player = turns.getCurrentTurn();
	Card* play = player->play(card);

	if(play == nullptr){
		std::cerr<<"Invalid play: "<<player->getName()<<" does not have that card!\n";
		return false;
	}

	switch (card->getType()) {
		case REVERSE:
			playReverseCard();
			break;
		case SKIP:
			playSkipCard();
			break;
		case DRAW_2: 
			playDrawCard(2);
			break;
		case DRAW_4: 
			playDrawCard(4);
		case WILD: 
			playChangeColor(card->getColor());
			break;
		default:
			std::cout<<"Played a number card.\n";
	}

	turns.goNext();
	field.push_back(card);

	return true;
}

void Game::playReverseCard(){
	std::cout<<"Played reverse card\n";
	turns.reverseTurns();

	// INFO: This should only be here for 2 players
	turns.goNext();
}

void Game::playSkipCard(){
	std::cout<<"Played skip card\n";
	turns.goNext();
}

void Game::playDrawCard(int number){
	std::cout<<"Played a +"<<number<<" card\n";
	turns.goNext();
	for(int i=0; i<number; ++i)
		draw();
}

void Game::playChangeColor(Color color){
	std::cout<<"Played wild card\n";
}

void Game::refillDeck(){
	for(Card* card: field){
		// WARNING: The deck does not refill if the players have all the cards
		if(field.size() == 1) break;
		deck.push_back(field.front());
		field.erase(field.begin());
	}
}

Card* Game::getCardOnField(){ return field.back(); }

Player* Game::getCurrentPlayerTurn(){ return turns.getCurrentTurn(); }

gameState Game::getGameState(){ return state; }

void Game::displayCards(std::vector<Card*> cards){
	for(Card* card : cards)
		std::cout<<card->getValue()<<" of "<<card->getColorString()<<std::endl;
}

void Game::displayPlayerCards(Player* player){
	std::cout<<player->getName()<<"'s cards: \n";
	displayCards(player->getCards());
}
