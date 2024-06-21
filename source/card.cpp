#include "Card.hpp"

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
