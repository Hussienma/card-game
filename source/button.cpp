#include "UI.hpp"
#include "Game.hpp"

Button::Button(Text* text, SDL_Color color, SDL_Rect position, GraphicsComponent* graphics, InputComponent* input): text(text), color(color), UI(position, graphics, input){
	this->position.x = position.x - position.w/2;
	this->position.y = position.y - position.h/2;

	graphics->setColor(color.r, color.g, color.b);

	Uint8 hoverColorR = (color.r+20)%255;
	Uint8 hoverColorG = (color.g+20)%255;
	Uint8 hoverColorB = (color.b+20)%255;
	hoverColor = { hoverColorR, hoverColorG, hoverColorB };
}

void Button::update(Game& game){
	mouseX = mouseY = 0;
	UI::update(game);
	if(checkCollision(mouseX, mouseY)){
		onPress(game);
	}
}

void Button::render(){
	if(hovering)
		graphics->setColor(hoverColor.r, hoverColor.g, hoverColor.b);
	else
		graphics->setColor(color.r, color.g, color.b);

	if(visible){
		UI::render();
		text->render();
	}
}

void QuitButton::onPress(Game& game){
	game.state = QUIT;
}

void RestartButton::onPress(Game& game){
	game.state = RESTART;
}
