#pragma once
#include "Entity.hpp"
#include <iostream>
#include <SDL2/SDL_render.h>

enum Color{ RED, YELLOW, GREEN, BLUE };

class Card: public Entity {
private:
	Color color;
	Uint16 value;
public:
	Card(Color color, Uint16 value, SDL_Texture* tex) : color(color), value(value), Entity(0,0,tex){}
	Color getColor();
	std::string getColorString();
	Uint16 getValue();
};
