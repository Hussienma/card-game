#include "Controller.hpp"
#include "Index.hpp"
#include "UI.hpp"
#include <SDL2/SDL_timer.h>
#include "InputComponent.hpp"

void PlayerInputComponent::update(Game& game, Player& player){
	SDL_Event* event = Controller::event;
	switch(event->type){
		case SDL_MOUSEBUTTONDOWN:
			for(int i=player.getCards().size()-1; i>=0; --i){
				Card* card = player.getCards().at(i);
				if(card->checkCollision(event->button.x, event->button.y)){
					/* std::cout<<"Clicked on "<<card->to_string()<<std::endl; */
					game.play(card);
					break;
				}
			}
			break;
		case SDL_MOUSEMOTION:{
			bool foundHover = false;
			for(int i=player.getCards().size()-1; i>=0; --i){
				Card* card = player.getCards().at(i);
				if(!foundHover && card->checkCollision(event->button.x, event->button.y)){
					card->hover = true;
					foundHover = true;
				} else {
					card->hover = false;
				}
			}
			break;
		}
		case SDL_KEYDOWN:
			if(event->key.keysym.sym == SDLK_SPACE){
				game.drawAndGoNext();
			}
			break;
	}
}

void PlayerAIInputComponent::update(Game& game, Player& player){
	std::vector<Card*> cards = player.getCards();
	Card* cardOnField = game.getCardOnField();

	SDL_Delay(1000);

	for(Card* card: cards){
		if(cardOnField == nullptr 
			|| (cardOnField->getType() != WILD && cardOnField->getType() != DRAW_4 && card->getColor() == cardOnField->getColor())
			|| ((cardOnField->getType() == WILD || cardOnField->getType() == DRAW_4) && card->getColor() == ColorWheel::selectedColor)
			|| card->getValue() == cardOnField->getValue()
			|| card->getType() == WILD
			|| card->getType() == DRAW_4){
			game.play(card);
			if(card->getType() == WILD || card->getType() == DRAW_4){
				ColorWheel::selectedColor = player.getDominantColor();
				std::cout<<player.getName()<<" has selected the color: "<<ColorWheel::selectedColor<<std::endl;
			}
			return;
		}
	}
	game.drawAndGoNext();
}

void UIInputComponent::update(Game& game, UI& ui){
	SDL_Event* event = Controller::event;
	if(event != nullptr)
		switch(event->type){
			case SDL_QUIT:
				game.state = QUIT;
				break;
			case SDL_MOUSEBUTTONDOWN:
				ui.mouseX = event->button.x;
				ui.mouseY = event->button.y;
				break;
			case SDL_MOUSEMOTION:
				if(ui.checkCollision(event->button.x, event->button.y)){
					ui.hovering = true;
				}
				else{
					ui.hovering = false;
				}
				break;
		}
}
