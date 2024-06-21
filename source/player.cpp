#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

void Player::draw(Card* card){
	cards.push_back(card);
	std::cout<<name<<" drew a "<<card->getColorString()<<" "<<card->getValue()<<std::endl;
}

Card* Player::play(Card* card){
	ptrdiff_t pos = std::distance(cards.begin(), std::find(cards.begin(), cards.end(), card));
	if(pos >= cards.size()){
		std::cout<<"Invalid play: card played not found!\n";
		return NULL;
	}
//	std::cout<<"The card is at: "<<pos<<", vector size: "<<cards.size()<<std::endl;
	cards.erase(cards.begin()+pos);
	std::cout<<name<<" played a "<<card->getColorString()<<" "<<card->getValue()<<std::endl;
	return card;
}

void Player::sortCards(){
	std::sort(cards.begin(), cards.end());
	int i=0;
	for(Card* card: cards){
		card->updatePos(i, card->getPos().y);
		i += card->getPos().w;
	}
}

std::string Player::getName(){ return name; }

std::vector<Card*> Player::getCards(){ return cards; }
