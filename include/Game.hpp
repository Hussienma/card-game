#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <map>

#include "Index.hpp"
#include "GameObject.hpp"
#include "LinkedList.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include "Text.hpp"

enum GameState { START, TURNS, PICK_COLOR, FINISHED, RESTART, QUIT };

class Game{
private:
	RenderWindow* window;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, UI*> UIs;
	std::vector<Sprite*> cardsSprites;
	std::vector<Card> cards;
	std::vector<Card*> deck;
	std::vector<Card*> field;
	Player* player;
	Player* opponent;
	Player* winner = nullptr;
	Text* winnerText = nullptr;
	LinkedList turns;
	Sprite* cardBack;
	bool playedWildCard = false;

	void initializeTextures();
	void initializeCards();
	void initializeUIs();
	void initializeGame();
	void restart();
	void draw();
public:
	GameState state;
	Game();
	Game(RenderWindow& window);
	~Game();
	void render();
	void drawUI();
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
	GameState getGameState();
	void displayCards(std::vector<Card*> cards);
	void displayPlayerCards(Player* player);
	void cleanUp();
};
