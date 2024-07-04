#pragma once
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>

#include "Card.hpp"
#include "LinkedList.hpp"
#include "Player.hpp"

enum gameState { START, TURNS, PICK_COLOR, FINISHED };

class Game{
private:
	std::vector<Card> cards;
	std::vector<Card*> deck;
	std::vector<Card*> field;
	Player* player;
	LinkedList turns;
	gameState state;
	void initializeCards(SDL_Texture* cardsTexture);
	void draw();
public:
	Game(std::vector<Player*>& player, SDL_Texture* cardsTexture);
	void drawAndGoNext();
	bool play(Card* card);
	void playReverseCard();
	void playSkipCard();
	void playDrawCard(int number);
	void playChangeColor(Color color);
	void refillDeck();
	void setState(gameState state);
	Card* getCardOnField();
	Player* getCurrentPlayerTurn();
	gameState getGameState();
	void displayCards(std::vector<Card*> cards);
	void displayPlayerCards(Player* player);
};
