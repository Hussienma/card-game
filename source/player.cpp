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
		return NULL;
	}

	cards.erase(cards.begin()+pos);
	std::cout<<name<<" played a "<<card->getColorString()<<" "<<card->getValue()<<std::endl;
	return card;
}

void Player::sortCards(){
	std::sort(cards.begin(), cards.end());

	int w = 96;
	int h = 128;
	int i = 128;
	for(Card* card: cards){
		int temp = i;
		card->unhover();
		card->updatePos(i, handLocation);
		card->resize(w, h);
		i += (w+300)/getCardsNumber();
		if(card != cards.back()){
			temp = i - temp;
			if(temp > w) temp = w;
			card->setCollider(temp, h);
		}
	}
}

std::string Player::getName(){ return name; }

int Player::getCardsNumber(){ return cards.size(); }

std::vector<Card*> Player::getCards(){ return cards; }
