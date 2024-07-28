#include "UI.hpp"
#include "GameObject.hpp"
#include "Utils.hpp"

void UI::update(Game& game){
	mouseX = mouseY = 0;
	input->update(game, *this);
}

void UI::render(){
	if(visible)
		graphics->update(*this);
}

void UI::animate(){
	if(hoverAnimation == nullptr)
		return;
	if(hoverAnimation->finished)
		hoverAnimation->currentFrame--;
	else
		hoverAnimation->currentFrame++;

	if(hoverAnimation->currentFrame%3==0){
		float changeRate = (float)hoverAnimation->currentFrame/hoverAnimation->totalFrames;
		position.y = utils::lerp(CENTER_VER-50, CENTER_VER-40, utils::easeInOut(changeRate))-position.h/2;
	}

	if(hoverAnimation->currentFrame == hoverAnimation->totalFrames)
		hoverAnimation->finished = true;
	else if(hoverAnimation->currentFrame == 0)
		hoverAnimation->finished = false;
}

Color ColorWheel::selectedColor;

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
}

void ColorWheel::render(){
	if(visible)
		graphics->update(*this);
}
