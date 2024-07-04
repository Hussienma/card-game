#include "Player.hpp"
#include "Constants.h"

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
		std::cout<<"Pos outside of bounds\n";
		return nullptr;
	}

	cards.erase(cards.begin()+pos);
	std::cout<<name<<" played a "<<card->getColorString()<<" "<<card->getValue()<<std::endl;
	return card;
}

void Player::sortCards(){
	std::sort(cards.begin(), cards.end());

	int i = 128;
	for(Card* card: cards){
		int temp = i;
		card->setHover(false);
		card->updatePos(i, handLocation);
		card->resize(CARD_WIDTH, CARD_HEIGHT);
		i += (400)/getCardsNumber();
		if(card != cards.back()){
			temp = i - temp;
			if(temp > CARD_WIDTH) temp = CARD_WIDTH;
			card->setCollider(temp, CARD_HEIGHT);
		}
	}
}

std::string Player::getName(){ return name; }

int Player::getCardsNumber(){ return cards.size(); }

std::vector<Card*> Player::getCards(){ return cards; }
