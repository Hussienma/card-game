#include "Index.hpp"
#include "InputComponent.hpp"

void PlayerInputComponent::update(Game& game, Player& player){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
				for(int i=player.getCards().size()-1; i>=0; --i){
					Card* card = player.getCards().at(i);
					if(card->checkCollision(event.button.x, event.button.y)){
						std::cout<<"Clicked on "<<card->to_string()<<std::endl;
						game.play(card);
						break;
					}
				}
				break;
			case SDL_MOUSEMOTION:{
				bool foundHover = false;
				for(int i=player.getCards().size()-1; i>=0; --i){
					Card* card = player.getCards().at(i);
					if(!foundHover && card->checkCollision(event.button.x, event.button.y)){
						card->hover = true;
						foundHover = true;
					} else {
						card->hover = false;
					}
				}
				break;
			}
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_SPACE){
					game.drawAndGoNext();
				}
				break;
			case SDL_QUIT:
				game.state = QUIT;
				break;
		}
	}
}

void UIInputComponent::update(Game& game, UI& ui){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				game.state = QUIT;
				break;
			case SDL_MOUSEBUTTONDOWN:
				ui.mouseX = event.button.x;
				ui.mouseY = event.button.y;
				break;
		}
	}
}
