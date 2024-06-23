
#include "Game.hpp"
#include <SDL2/SDL_render.h>
#include <cstdlib>

Game::Game(Player* player, std::vector<Card>& cards){
	this->player = player;
	state = START;

	for(int i=0; i<cards.size(); i++){
		deck.push_back(&cards[i]);
	}
}

void Game::draw(Player* player){
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

bool Game::play(Player* player, Card* card){
	if(field.size() != 0 && field.back()->getColor() != card->getColor() && field.back()->getValue() != card->getValue()){
		std::cerr<<"Invalid play: card isn't the same color or number.\n";
		return false;
	}

	Card* play = player->play(card);
	if(play == NULL){
		std::cerr<<"Invalid play: "<<player->getName()<<" does not have that card!\n";
		return false;
	}
	field.push_back(card);
	std::cout<<"Card on the field: "<<field.back()->getValue()<<" of " << field.back()->getColorString()<<std::endl;
	return true;
}

void Game::refillDeck(){
	for(Card* card: field){
		if(field.size() == 1) break;
		deck.push_back(field.front());
		field.erase(field.begin());
	}
}

Card* Game::getCardOnField(){ return field.back(); }

void Game::displayCards(std::vector<Card*> cards){
	for(Card* card : cards)
		std::cout<<card->getValue()<<" of "<<card->getColorString()<<std::endl;
}

void Game::displayPlayerCards(Player* player){
	std::cout<<player->getName()<<"'s cards: \n";
	displayCards(player->getCards());
}
