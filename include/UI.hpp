#pragma once
#include "InputComponent.hpp"
#include "Text.hpp"
#include "Constants.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

struct Animation;

class UI {
	public:
	GraphicsComponent* graphics;
	InputComponent* input;
	Animation* hoverAnimation;
	SDL_Rect position;
	int mouseX, mouseY;
	bool visible = false;
	bool hovering = false;
	UI(){}
	UI(SDL_Rect position, GraphicsComponent* graphics): position(position), graphics(graphics){
		this->position.x = position.x-position.w/2;
		this->position.y = position.y-position.h/2;
	}
	UI(SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): position(position), graphics(graphics), input(input){
		this->position.x = CENTER_HOR-position.w/2;
		this->position.y = CENTER_VER-position.h/2;
	}
	virtual void update(Game& game);
	virtual void render();
	bool checkCollision(int x, int y){
		return (x>= position.x && x <= position.x + position.w)
		&& (y >= position.y && y <= position.y + position.h);
	}
	virtual void animate();
};

class ColorWheel: public UI {
	public:
	static Color selectedColor;
	ColorWheel();
	ColorWheel(SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): UI(position, graphics, input){}
	virtual void update(Game& game);
	virtual void render();
};

class Button: public UI {
	private:
	Text* text;
	public:
	SDL_Color color;
	SDL_Color hoverColor;
	Button(){}
	Button(Text* text, SDL_Color color, SDL_Rect position, GraphicsComponent* graphics, InputComponent* input);

	void update(Game& game);
	void render();
	virtual void onPress(Game& game){}
};

class RestartButton: public Button {
	public:
	RestartButton();
	RestartButton(Text* text, SDL_Color color, SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): Button(text, color, position, graphics, input){}
	void onPress(Game& game) override;
};

class QuitButton: public Button {
	public:
	QuitButton(){}
	QuitButton(Text* text, SDL_Color color, SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): Button(text, color, position, graphics, input){}
	void onPress(Game& game) override;
};

class PlayButton: public Button {
	public:
	ApplicationState* state;
	PlayButton(){}
	PlayButton(ApplicationState& state, Text* text, SDL_Color color, SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): state(&state), Button(text, color, position, graphics, input){}
	void onPress(Game& game) override { *state = IN_GAME; }
};

