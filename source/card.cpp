#include "Card.hpp"
#include "Utils.hpp"
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
		case WILD:
			return "Wild";
	default:
			return "Unknown";
	}
}

void Card::setHover(bool val){
	hovering = val;
}

void Card::animate(){
	if((hovering && frame == 40) || (!hovering && frame == 0)) return;
	if(hovering) frame++;
	else frame--;
	int x = getPos().x;
	int y = utils::lerp(368, 328, (float)frame/40);
	updatePos(x, y);
	setCollider(getCollider().w, getCollider().h + y);
}
