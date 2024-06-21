#include <algorithm>

#include "Game.hpp"
#include <SDL2/SDL_render.h>
#include <cstdlib>

Game::Game(Player* player, std::vector<Card>& cards){
	this->player = player;
	state = START;

	for(int i=0; i<10; i++){
		deck.push_back(&cards[i]);
//		std::cout<<deck[i]->getColorString()<<deck[i]->getValue()<<" was added to deck\n";
	}
}

void Game::draw(Player* player){
	if(deck.size() == 0){
		std::cerr<<"Deck is empty!\n";
		return;
	}

	int pos = rand() % deck.size();
	Card* card = deck[pos];
	deck.erase(deck.begin()+pos);
	player->draw(card);
}

void Game::play(Player* player, Card* card){
	Card* play = player->play(card);
	if(play == NULL){
		std::cerr<<"Invalid play: "<<player->getName()<<" does not have that card!\n";
		return;
	}
	field.push_back(card);
	std::cout<<"Cards on field: \t";
	displayCards(field);
}

void Game::displayCards(std::vector<Card*> cards){
	for(Card* card : cards)
		std::cout<<card->getValue()<<" of "<<card->getColorString()<<std::endl;
}

void Game::displayPlayerCards(Player* player){
	std::cout<<player->getName()<<"'s cards: \n";
	displayCards(player->getCards());
}
