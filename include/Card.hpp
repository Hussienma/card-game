#pragma once
#include "Entity.hpp"
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
	virtual Color getColor();
	std::string getColorString();
	Uint16 getValue();
	void animate();
	void setHover(bool val);
	void setColor(Color color);
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
	private:
	Color precievedColor;
	public:
	ChangeColorCard(Uint16 value, SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex): precievedColor(WILD), Card(WILD, value, pos, frame, tex){}
	Color getColor();
	void setColor(Color color);
};

class DrawCardsCard: public Card{
	public:
	DrawCardsCard(Color color, SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex): Card(color, 12, pos, frame, tex){}
};

class DrawAndChangeColorCard: public ChangeColorCard{
	public:
	DrawAndChangeColorCard(SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex):  ChangeColorCard(14, pos, frame, tex){}
};

