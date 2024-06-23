#pragma once
#include "Card.hpp"
#include <vector>

class Player{
private:
	Uint16 size;
	std::vector<Card*> cards;
	std::string name;
	int handLocation;
public:
	Player(std::string name, int location) : name(name), handLocation(location), size(0){}
	void draw(Card* card);
	Card* play(Card* card);
	void sortCards();
	std::string getName();
	std::vector<Card*> getCards();
};
