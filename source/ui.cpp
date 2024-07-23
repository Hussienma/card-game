#include "UI.hpp"

void UI::update(Game& game){
	input->update(game, *this);
	if(visible)
		graphics->update(*this);
}

void ColorWheel::update(Game& game){
	mouseX = mouseY = 0;
	input->update(game, *this);
	
	int halfPointX = position.x + (position.w)/2;
	int halfPointY = position.y + (position.h)/2;

	if(checkCollision(mouseX, mouseY)){
		if(mouseX < halfPointX && mouseY < halfPointY)
			selectedColor = RED;
		else if(mouseX > halfPointX && mouseY < halfPointY)
			selectedColor = GREEN;
		else if(mouseX < halfPointX && mouseY > halfPointY)
			selectedColor = BLUE;
		else
			selectedColor = YELLOW;
		visible = false;
		game.state = TURNS;
		std::cout<<"Selected: "<<selectedColor<<std::endl;
	}

	if(visible)
		graphics->update(*this);
}
