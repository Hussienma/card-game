
#include "Game.hpp"
#include "LinkedList.hpp"
#include <SDL2/SDL_render.h>
#include <cstdlib>

Game::Game(std::vector<Player*>& players, SDL_Texture* cardsTexture): state(START), turns(*players[0], *players[1]){
	initializeCards(cardsTexture);
	player = players[0];
	for(int i=0; i<cards.size(); i++){
		deck.push_back(&cards[i]);
	}

	for(int i=0; i<10; ++i){
		draw(players[0]);
		draw(players[1]);
	}
	players[0]->sortCards();
	players[1]->sortCards();
}

void Game::initializeCards(SDL_Texture* cardsTexture){
	Color color;
	SDL_Rect frame;
	frame.x = 0;
	frame.w = 192;
	frame.h = 256;

	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;
	pos.w = 96;
	pos.h = 128;

	for(int i=0; i<4; ++i){
		switch(i){
			case 0: color = BLUE; frame.y = 0; break;
			case 1: color = GREEN; frame.y = 256; break;
			case 2: color = RED; frame.y = 512; break;
			case 3: color = YELLOW; frame.y = 768; break;
		}

		frame.x = 0;
		cards.push_back(Card(color, 0, pos, frame, cardsTexture));

		frame.x = 192;
		for(int j=1; j<10; ++j){
			Card card = Card(color, j, pos, frame, cardsTexture);
			cards.push_back(card);
			cards.push_back(card);
			frame.x += 192;
		}

		for(int j=0; j<2; ++j){
			cards.push_back(ReverseCard(color, pos, frame, cardsTexture));
		}

		frame.x += 192;
		for(int j=0; j<2; ++j){
			cards.push_back(DrawCardsCard(color, 2, pos, frame, cardsTexture));
		}

		frame.x += 192;
		for(int j=0; j<2; ++j){
			cards.push_back(SkipCard(color, pos, frame, cardsTexture));
		}
	}

	frame.x += 192;
	frame.y = 0;
	for(int i=0; i<4; ++i)
		cards.push_back(ChangeColorCard(pos, frame, cardsTexture));

	frame.y = 256;
	for(int i=0; i<4; ++i)
		cards.push_back(DrawCardsCard(WILD, 4, pos, frame, cardsTexture));

}

void Game::draw(Player* player){
	if(deck.size() == 0){
		std::cout<<"Refilling deck!\n";
		refillDeck();
		if(deck.size() == 0){
			std::cerr<<"Deck & field are empty!\n";
			return;
		}
	}
	
	std::srand(time(NULL));

	int pos = rand();
	pos %= deck.size();

	Card* card = deck[pos];
	deck.erase(deck.begin()+pos);
	player->draw(card);
}

bool Game::play(Player* player, Card* card){
	if(field.size() != 0 && field.back()->getColor() != card->getColor() && field.back()->getValue() != card->getValue()){
		std::cerr<<"Invalid play: card isn't the same color or number.\n";
		return false;
	}

	Card* play = player->play(card);
	turns.goNext();
	if(play == NULL){
		std::cerr<<"Invalid play: "<<player->getName()<<" does not have that card!\n";
		return false;
	}
	field.push_back(card);
	std::cout<<"Card on the field: "<<field.back()->getValue()<<" of " << field.back()->getColorString()<<std::endl;
	std::cout<<turns.getCurrentTurn()->getName()<<" turn now.\n";
	return true;
}

void Game::refillDeck(){
	for(Card* card: field){
		if(field.size() == 1) break;
		deck.push_back(field.front());
		field.erase(field.begin());
	}
}

Card* Game::getCardOnField(){ return field.back(); }

void Game::displayCards(std::vector<Card*> cards){
	for(Card* card : cards)
		std::cout<<card->getValue()<<" of "<<card->getColorString()<<std::endl;
}

void Game::displayPlayerCards(Player* player){
	std::cout<<player->getName()<<"'s cards: \n";
	displayCards(player->getCards());
}
