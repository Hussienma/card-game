#include "UI.hpp"
#include "Game.hpp"

Button::Button(Text* text, SDL_Color color, SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): text(text), UI(position, graphics, input){
	this->position.x = position.x - position.w/2;
	this->position.y = position.y - position.h/2;

	graphics->setColor(color.r, color.g, color.b);
}

void Button::update(Game& game){
	mouseX = mouseY = 0;
	UI::update(game);
	if(checkCollision(mouseX, mouseY)){
		onPress(game);
	}
}

void Button::render(){
	if(visible){
		UI::render();
		text->render();
	}
}

void RestartButton::onPress(Game& game){
	game.state = RESTART;
}
