#pragma once
#include "GameObject.hpp"
#include "Index.hpp"
#include <map>
#include <vector>

class Player{
private:
	Uint16 size = 0;
	std::vector<Card*> cards;
	std::string name;
	int handLocation = 352;
	InputComponent* input;
	std::map<Color, int> numberOfCardsByColor;

public:
	Player() : name(" "){}
	Player(std::string name) : name(name){}
	Player(std::string name, InputComponent* input) : name(name), input(input){}
	void update(Game& game);
	void render();
	void draw(Card* card);
	Card* play(Card* card);
	void sortCards();
	std::string getName();
	int getCardsNumber();
	Color getDominantColor();
	std::vector<Card*> getCards();
};
