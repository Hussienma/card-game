#pragma once
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>

#include "Card.hpp"
#include "LinkedList.hpp"
#include "Player.hpp"

enum game_state { START, IN_PROGRESS, FINISHED };

class Game{
private:
	std::vector<Card> cards;
	std::vector<Card*> deck;
	std::vector<Card*> field;
	Player* player;
	LinkedList turns;
	game_state state;
	void initializeCards(SDL_Texture* cardsTexture);
public:
	Game(std::vector<Player*>& player, SDL_Texture* cardsTexture);
	void draw(Player* player);
	bool play(Player* player, Card* card);
	void refillDeck();
	Card* getCardOnField();
	void displayCards(std::vector<Card*> cards);
	void displayPlayerCards(Player* player);
};
