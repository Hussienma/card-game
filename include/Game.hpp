#pragma once
#include <iostream>
#include <vector>

#include "Card.hpp"
#include "Player.hpp"

enum game_state { START, IN_PROGRESS, FINISHED };

class Game{
private:
	std::vector<Card*> deck;
	std::vector<Card*> field;
	Player* player;
	game_state state;
public:
	Game(Player* player, std::vector<Card>& cards);
	void draw(Player* player);
	bool play(Player* player, Card* card);
	void refillDeck();
	Card* getCardOnField();
	void displayCards(std::vector<Card*> cards);
	void displayPlayerCards(Player* player);
};
