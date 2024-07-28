#include "GameObject.hpp"

void GameObject::update(){
//	std::cout<<"GameObject update method\n";
}

void Card::update(){
	if(hover && hoverAnimation.currentFrame < hoverAnimation.totalFrames)
		hoverAnimation.currentFrame++;
	else if(!hover && hoverAnimation.currentFrame > 0)
		hoverAnimation.currentFrame--;

	float changeRate = (float)hoverAnimation.currentFrame/hoverAnimation.totalFrames;
	position.y = utils::lerp(WINDOW_HEIGHT - CARD_HEIGHT, WINDOW_HEIGHT - CARD_HEIGHT - ((float)CARD_HEIGHT/4), utils::easeInOut(changeRate));
}

void GameObject::render(){
	graphics->update(*this);
}

void GraphicsComponent::update(UI& ui){
	if (renderShadows) {
		SDL_Rect shadowPosition = ui.position;
		if(ui.hovering){
			shadowPosition.x -= 3;
			shadowPosition.y += 4;
		}
		else {
			shadowPosition.x -= 1;
			shadowPosition.y += 2;
		}
		window->render(sprite->shadowTexture, shadowPosition);
	}

	window->render(sprite->texture, sprite->frame, ui.position);
}

void GraphicsComponent::setColor(Uint8 r, Uint8 g, Uint8 b){
	window->changeTextureColor(sprite->texture, r, g, b);
}

