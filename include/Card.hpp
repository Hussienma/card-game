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
public:
	Card(Color color, Uint16 value, SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex);
	Color getColor();
	std::string getColorString();
	Uint16 getValue();
	void hover();
	void unhover();
};
