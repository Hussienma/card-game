#pragma once
#include "Entity.hpp"
#include "Utils.hpp"
#include <iostream>
#include <SDL2/SDL_render.h>

enum Color{ RED, YELLOW, GREEN, BLUE, WILD };

class Card: public Entity {
private:
	Color color;
	Uint16 value;
	bool hovering;
	int frame = 0;
	void useAbility();
public:
	Card(Color color, Uint16 value, SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex);
	Color getColor();
	std::string getColorString();
	Uint16 getValue();
	void animate();
	void setHover(bool val);
};

class ReverseCard: public Card{
public:
	ReverseCard(Color color, SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex): Card(color, 10, pos, frame, tex){}
};

class SkipCard: public Card{
	public:
	SkipCard(Color color, SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex): Card(color, 11, pos, frame, tex){}
};

class ChangeColorCard: public Card{
	public:
	ChangeColorCard(SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex): Card(WILD, 13, pos, frame, tex){}
};

class DrawCardsCard: public Card{
	private:
	Uint16 numberOfCards;
	public:
	DrawCardsCard(Color color, Uint16 number, SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex): numberOfCards(number), Card(color, 12, pos, frame, tex){}
	Uint16 getNumberOfCards();
};

