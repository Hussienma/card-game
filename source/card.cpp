#include "Card.hpp"
#include <SDL2/SDL_render.h>

Card::Card(Color color, Uint16 value, SDL_Rect pos, SDL_Rect frame, SDL_Texture* tex) : color(color), value(value), Entity(pos, frame, tex){

}
Color Card::getColor(){ return color; }

Uint16 Card::getValue(){ return value; }

std::string Card::getColorString(){
	switch (color) {
		case RED: 
			return "Red";
		case BLUE:
			return "Blue";
		case GREEN:
			return "Green";
		case YELLOW:
			return "Yellow";
		default:
			return "Unknown";
	}
}

void Card::hover(){
	if(hovering) return;
	int x = getPos().x;
	int y = getPos().y - (getPos().h / 2);
	updatePos(x, y);
	setCollider(getCollider().w, getCollider().h + y);
	hovering = true;
}

void Card::unhover(){
	if(!hovering) return;
	int x = getPos().x;
	int y = getPos().y + (getPos().h / 2);
	updatePos(x, y);
	setCollider(getCollider().w, getCollider().h + y - getPos().y);
	hovering = false;
}
