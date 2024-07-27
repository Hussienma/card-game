#include "Player.hpp"
#include "Constants.h"

#include <algorithm>
#include <iostream>
#include <vector>

void Player::update(Game& game){
	input->update(game, *this);
	for(Card* card: cards){
		card->update();
	}
}

void Player::render(){
	for(Card* card: cards)
		card->render();
}

void Player::draw(Card* card){
	card->position.x = handLocation;
	card->position.w = CARD_WIDTH;
	card->position.h = CARD_HEIGHT;

	if(!numberOfCardsByColor[card->getColor()])
		numberOfCardsByColor[card->getColor()] = 0;

	numberOfCardsByColor[card->getColor()] += 1;
	cards.push_back(card);
	std::cout<<name<<" drew a "<<card->getColorString()<<" "<<card->getValue()<<std::endl;
	std::cout<<getName()<<"'s current dominant color is: "<<getDominantColor()<<std::endl;
}

Card* Player::play(Card* card){
	ptrdiff_t pos = std::distance(cards.begin(), std::find(cards.begin(), cards.end(), card));
	if(pos >= cards.size()){
		std::cout<<getName()<<" does not have that card: Array position out of bounds\n";
		return nullptr;
	}

	numberOfCardsByColor[card->getColor()] -= 1;

	cards.erase(cards.begin()+pos);
	std::cout<<name<<" played a "<<card->getColorString()<<" "<<card->getValue()<<std::endl;
	return card;
}

void Player::sortCards(){
	std::sort(cards.begin(), cards.end());

	int i = 128;
	for(Card* card: cards){
		int temp = i;
		card->hover = false;
		card->position.x = i;
		// INFO: the y position was set to hand position
		card->position.y = handLocation;

		card->position.w = CARD_WIDTH;
		card->position.h = CARD_HEIGHT;
		i += (400)/getCardsNumber();
	}
}

std::string Player::getName(){ return name; }

int Player::getCardsNumber(){ return cards.size(); }

std::vector<Card*> Player::getCards(){ return cards; }

Color Player::getDominantColor(){
	std::pair<Color, int> domPair = std::make_pair(RED, 0);
	std::map<Color, int>::iterator currentPair;
	for(currentPair = numberOfCardsByColor.begin(); currentPair != numberOfCardsByColor.end(); ++currentPair){
		if(currentPair->second > domPair.second)
			domPair = std::make_pair(currentPair->first, currentPair->second);
	}

	return domPair.first;
}
