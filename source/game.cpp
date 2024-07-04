#include "Game.hpp"
#include "Card.hpp"
#include "LinkedList.hpp"
#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <string>

Game::Game(std::vector<Player*>& players, SDL_Texture* cardsTexture): state(START), turns(*players[0], *players[1]){
	initializeCards(cardsTexture);
	player = players[0];
	for(int i=0; i<cards.size(); i++){
		deck.push_back(&cards[i]);
	}

	for(int i=0; i<20; ++i){
		draw();
		turns.goNext();
	}
	players[0]->sortCards();
	players[1]->sortCards();

	state = TURNS;
}

void Game::initializeCards(SDL_Texture* cardsTexture){
	Color color;
	SDL_Rect frame;
	frame.x = 0;
	frame.w = 192;
	frame.h = 256;

	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;
	pos.w = 96;
	pos.h = 128;

	for(int i=0; i<4; ++i){
		switch(i){
			case 0: color = BLUE; break;
			case 1: color = GREEN; break;
			case 2: color = RED; break;
			case 3: color = YELLOW; break;
		}
		frame.y = i*256;
		frame.x = 0;
		cards.push_back(Card(color, 0, pos, frame, cardsTexture));

		frame.x = 192;
		for(int j=1; j<10; ++j){
			Card card = Card(color, j, pos, frame, cardsTexture);
			cards.push_back(card);
			cards.push_back(card);
			frame.x += 192;
		}

		for(int j=0; j<2; ++j){
			cards.push_back(ReverseCard(color, pos, frame, cardsTexture));
		}

		frame.x += 192;
		for(int j=0; j<2; ++j){
			cards.push_back(DrawCardsCard(color, pos, frame, cardsTexture));
		}

		frame.x += 192;
		for(int j=0; j<2; ++j){
			cards.push_back(SkipCard(color, pos, frame, cardsTexture));
		}
	}

	// WILD Change Color
	frame.x += 192;
	frame.y = 0;
	for(int i=0; i<4; ++i)
		cards.push_back(ChangeColorCard(13, pos, frame, cardsTexture));

	// WILD +4 cards
	frame.y = 256;
	for(int i=0; i<4; ++i)
		cards.push_back(DrawAndChangeColorCard(pos, frame, cardsTexture));
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
	if(field.size() > 0 && field.back()->getColor() == WILD){
		ChangeColorCard c = *(ChangeColorCard*)field.back();
		if(c.getColor() != card->getColor()){
			std::cerr<<"Invalid play: current color is: "<<c.getColor()<<std::endl;
			return false;
		}
	}

	else if(field.size() > 0 
		&& card->getColor() != WILD 
		&& field.back()->getColor() != card->getColor()
		&& field.back()->getValue() != card->getValue()){
		std::cerr<<"Invalid play: card isn't the same color or number.\n";
		return false;
	}

	Player* player = turns.getCurrentTurn();
	Card* play = player->play(card);

	if(play == nullptr){
		std::cerr<<"Invalid play: "<<player->getName()<<" does not have that card!\n";
		return false;
	}

	switch (play->getValue()) {
		case 10:
			playReverseCard();
			break;
		case 11:
			playSkipCard();
			break;
		case 12: {
			playDrawCard(2);
			break;
		}
		case 13: 
			playChangeColor(card->getColor());
			break;
		case 14: {
			playDrawCard(4);
			break;
		}
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

void Game::setState(gameState state){
	this->state = state;
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
