#pragma once
#include "InputComponent.hpp"
#include <SDL2/SDL_rect.h>

// TODO: Inhert UI from GameObject class
class UI {
	public:
	GraphicsComponent* graphics;
	InputComponent* input;
	SDL_Rect position;
	int mouseX, mouseY;
	bool visible = false;
	bool hovering = false;
	UI();
	UI(SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): position(position), graphics(graphics), input(input){}
	virtual void update(Game& game);
	bool checkCollision(int x, int y){
		return (x>= position.x && x <= position.x + position.w)
		&& (y >= position.y && y <= position.y + position.h);
	}
};

class ColorWheel: public UI {
	public:
	Color selectedColor;
	ColorWheel();
	ColorWheel(SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): UI(position, graphics, input){}
	virtual void update(Game& game);
};
