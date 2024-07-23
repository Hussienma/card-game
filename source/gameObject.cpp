#include "GameObject.hpp"
#include "Game.hpp"
#include "Player.hpp"

void GameObject::update(){
//	std::cout<<"GameObject update method\n";
}

void Card::update(){
	if(hover && hoverAnimation.currentFrame < hoverAnimation.totalFrames)
		hoverAnimation.currentFrame++;
	else if(!hover && hoverAnimation.currentFrame > 0)
		hoverAnimation.currentFrame--;

	float changeRate = (float)hoverAnimation.currentFrame/hoverAnimation.totalFrames;
	position.y = utils::lerp(352, 312, utils::easeInOut(changeRate));

	render();
}

void GameObject::render(){
	graphics->update(*this);
}

void GraphicsComponent::update(UI& ui){
	window->render(sprite->texture, sprite->frame, ui.position);
}

