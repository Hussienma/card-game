#pragma once
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>

#include "GameObject.hpp"
#include "LinkedList.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"

enum gameState { START, TURNS, PICK_COLOR, FINISHED, QUIT };

class Game{
private:
	RenderWindow* window;
	SDL_Texture* cardsTexture;
	std::vector<Sprite*> cardsSprites;
	std::vector<Card> cards;
	std::vector<Card*> deck;
	std::vector<Card*> field;
	Player* player;
	Player* opponent;
	LinkedList turns;
	void initializeCards();
	void draw();
public:
	gameState state;
	Game(RenderWindow& window);
	void render();
	void update();
	void drawAndGoNext();
	bool play(Card* card);
	void playReverseCard();
	void playSkipCard();
	void playDrawCard(int number);
	void playChangeColor(Color color);
	void refillDeck();
	Card* getCardOnField();
	Player* getCurrentPlayerTurn();
	gameState getGameState();
	void displayCards(std::vector<Card*> cards);
	void displayPlayerCards(Player* player);
};
