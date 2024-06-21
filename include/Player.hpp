#pragma once
#include "Card.hpp"
#include <vector>

class Player{
private:
	Uint16 size;
	std::vector<Card*> cards;
	std::string name;
public:
	Player(std::string name) : name(name), size(0){}
	void draw(Card* card);
	Card* play(Card* card);
	void sortCards();
	std::string getName();
	std::vector<Card*> getCards();
};
