#include "Game.hpp"
#include "Constants.h"
#include "Controller.hpp"
#include "GameObject.hpp"
#include "InputComponent.hpp"
#include "LinkedList.hpp"
#include "Text.hpp"
#include "UI.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>

// TODO: 1. UI to indicate turn
// 2. UI to indicate the chosen color

Game::Game(RenderWindow& window): window(&window), state(START){
	initializeTextures();
	initializeCards();
	initializeUIs();

	initializeGame();
}

Game::~Game(){
	delete UIs["color wheel"];
	delete UIs["restart button"];

	window->destroyTexture(textures["cards"]);
	window->destroyTexture(textures["color wheel"]);
	window->destroyTexture(textures["button"]);
	delete player;
	delete opponent;
}

void Game::initializeGame(){
	player = new Player("Player 1", new PlayerInputComponent());
	opponent = new Player("Player 2", new PlayerAIInputComponent());
	for(Uint16 i=0; i<cards.size(); i++){
		deck.push_back(&cards[i]);
	}

	turns.insertPlayer(*player);
	turns.insertPlayer(*opponent);

	for(int i=0; i<20; ++i){
		draw();
		turns.goNext();
	}
	player->sortCards();
	opponent->sortCards();

	state = TURNS;
}

void Game::restart(){
	state = START;
	delete player;
	delete opponent;

	deck.clear();
	field.clear();
	turns = LinkedList();
	winner = nullptr;
	winnerText = nullptr;
	playedWildCard = false;

	UIs["restart button"]->visible = false;
	initializeGame();
}

void Game::render(){
	if(field.size() > 0)
		field.back()->render();
	player->render();

	SDL_Rect oppHandLocation;
	if(opponent->getCardsNumber() != 0){
		int incrementBy = (WINDOW_WIDTH/2)/(opponent->getCardsNumber());
		oppHandLocation.x = WINDOW_WIDTH/4;
		oppHandLocation.y = 0;
		oppHandLocation.w = CARD_WIDTH;
		oppHandLocation.h = CARD_HEIGHT;
		for(Card* card: opponent->getCards()){
			window->render(cardBack->texture, cardBack->frame, oppHandLocation);
			oppHandLocation.x += incrementBy;
		}
	}
}

void Game::drawUI(){
	UIs["color wheel"]->render();
	SDL_Rect position;
	position.x = position.y = 0;
	position.w = 100;
	position.h = 74;
	if(winnerText != nullptr){
		UIs["frame"]->render();
		winnerText->render();
	}
	UIs["restart button"]->render();
}

void Game::update(){
	Controller::handleInput(*this);
	switch(state){
		case TURNS: {
			Player* player = turns.getCurrentTurn();
			player->update(*this);
			break;
		}
		case PICK_COLOR:
			UIs["color wheel"]->update(*this);
			break;
		case FINISHED:
			UIs["restart button"]->update(*this);
			break;
		case RESTART:
			restart();
			break;
		default:
			break;
	}
	
	// INFO: Do all the rendering here
	render();
	drawUI();
}

void Game::initializeTextures(){
	textures["cards"] = window->loadTexture("./gfx/Cards.png");
	textures["card shadow"] = window->loadTexture("./gfx/Shadow.png");
	textures["color wheel"] = window->loadTexture("./gfx/Color Wheel.png");
	textures["button"] = window->loadTexture("./gfx/Button.png");
	textures["frame"] = window->loadTexture("./gfx/Frame.png");
}

void Game::initializeUIs(){
	SDL_Rect position, frame;
	frame.x = frame.y = 0;
	frame.h = frame.w = 256;
	position.x = CENTER_HOR;
	position.y = CENTER_VER;
	position.h = position.w = 256;
	if(!UIs["color wheel"]){
		std::cout<<"Initializing color wheel...\n";
		UIs["color wheel"] = new ColorWheel(position, new GraphicsComponent(window, new Sprite(textures["color wheel"], frame)), new UIInputComponent());
	}

	if(!UIs["frame"])
		UIs["frame"] = new UI({CENTER_HOR, CENTER_VER, 350, 200}, new GraphicsComponent(window, new Sprite(textures["frame"], {0,0, 400, 400})));

	if(!UIs["restart button"])
		UIs["restart button"] = 
			new RestartButton(
				new Text(window, {255, 255, 255}, "Play Again!", "Sans", 24, CENTER_HOR, CENTER_VER+30),
				{0, 100, 50}, {CENTER_HOR, CENTER_VER+30, 150, 50},
				new GraphicsComponent(window, new Sprite(textures["button"], {0,0,200, 200})),
				new UIInputComponent()
			);
}

void Game::initializeCards(){
	Color color;
	SDL_Rect frame;
	frame.x = 0;
	frame.w = 192;
	frame.h = 256;

	for(int i=0; i<4; ++i){
		switch(i){
			case 0: color = BLUE; break;
			case 1: color = GREEN; break;
			case 2: color = RED; break;
			case 3: color = YELLOW; break;
		}
		frame.y = i*256;
		frame.x = 0;

		cards.push_back(Card(NUMBER, color, 0, new GraphicsComponent(window, new Sprite(textures["cards"], frame, textures["card shadow"]), true)));

		frame.x = 192;
		for(int j=1; j<10; ++j){
			Card card = Card(NUMBER, color, j, new GraphicsComponent(window, new Sprite(textures["cards"], frame, textures["card shadow"]), true));
			cards.push_back(card);
			cards.push_back(card);
			frame.x += 192;
		}

		for(int j=0; j<2; ++j){
			cards.push_back(
				Card(REVERSE, color, 10, new GraphicsComponent(window, new Sprite(textures["cards"], frame, textures["card shadow"]), true))
			);
		}

		frame.x += 192;
		for(int j=0; j<2; ++j){
			cards.push_back(
				Card(DRAW_2, color, 11, new GraphicsComponent(window, new Sprite(textures["cards"], frame, textures["card shadow"]), true))
			);
		}

		frame.x += 192;
		for(int j=0; j<2; ++j){
			cards.push_back(
				Card(SKIP, color, 12, new GraphicsComponent(window, new Sprite(textures["cards"], frame, textures["card shadow"]), true))
			);
		}
	}

	// WILD Change Color
	frame.x += 192;
	frame.y = 0;
	for(int i=0; i<4; ++i)
		cards.push_back(
			Card(WILD, color, 13, new GraphicsComponent(window, new Sprite(textures["cards"], frame, textures["card shadow"]), true))
		);

	// WILD +4 cards
	frame.y = 256;
	for(int i=0; i<4; ++i)
		cards.push_back(
			Card(DRAW_4, color, 14, new GraphicsComponent(window, new Sprite(textures["cards"], frame, textures["card shadow"]), true))
		);

	frame.y += 256;
	cardBack = new Sprite(textures["cards"], frame);
}

void Game::draw(){
	Player* player = turns.getCurrentTurn();
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
	player->sortCards();
}

void Game::drawAndGoNext(){
	draw();
	turns.goNext();
}

bool Game::play(Card* card){
	Card* cardOnField = nullptr;
	if(field.size() > 0)
		cardOnField = field.back(); 

	ColorWheel* wheel = (ColorWheel*)UIs["color wheel"];

	if(playedWildCard && (wheel->selectedColor != card->getColor() && card->getValue() < 13)){
		std::cerr<<"Invalid play: card isn't the chosen color.\n";
		return false;
	}

	else if(!playedWildCard && cardOnField != nullptr 
		&& card->getValue() < 13 
		&& cardOnField->getColor() != card->getColor()
		&& cardOnField->getValue() != card->getValue()){
		std::cerr<<"Invalid play: card isn't the same color or number.\n";
		return false;
	}

	Player* player = turns.getCurrentTurn();
	Card* play = player->play(card);

	if(play == nullptr){
		std::cerr<<"Invalid play: "<<player->getName()<<" does not have that card!\n";
		return false;
	}

	if(player->getCardsNumber() == 0){
		state = FINISHED;
		winner = player;
		std::cout<<winner->getName()<<" won the game!\n";
		winnerText = new Text(window, {0,0,0}, winner->getName() + " has won!", "Sans", 32, CENTER_HOR, CENTER_VER-60);
		UIs["restart button"]->visible = true;
		UIs["frame"]->visible = true;
		return true;
	}

	if(playedWildCard) playedWildCard = false;

	switch (card->getType()) {
		case REVERSE:
			playReverseCard();
			break;
		case SKIP:
			playSkipCard();
			break;
		case DRAW_2: 
			playDrawCard(2);
			break;
		case DRAW_4: 
			playDrawCard(4);
		case WILD: 
			playedWildCard = true;
			if(player == this->player)
				playChangeColor(card->getColor());
			break;
		default:
			std::cout<<"Played a number card.\n";
	}

	turns.goNext();
	card->hover = false;
	card->position.w /=1.2;
	card->position.h /=1.2;
	card->position.x = (CENTER_HOR-card->position.w/2);
	card->position.y = (CENTER_VER-card->position.h/2);

	field.push_back(card);

	player->sortCards();
	return true;
}

void Game::playReverseCard(){
	std::cout<<"Played reverse card\n";
	turns.reverseTurns();

	// WARNING: This should only be here for 2 players
	turns.goNext();
}

void Game::playSkipCard(){
	std::cout<<"Played skip card\n";
	turns.goNext();
}

void Game::playDrawCard(int number){
	std::cout<<"Played a +"<<number<<" card\n";
	turns.goNext();
	for(int i=0; i<number; ++i)
		draw();
}

void Game::playChangeColor(Color color){
	std::cout<<"Played wild card\n";
	UIs["color wheel"]->visible = true;
	state = PICK_COLOR;
}

void Game::refillDeck(){
	for(Card* card: field){
		if(field.size() == 1) break;
		deck.push_back(field.front());
		field.erase(field.begin());
	}
}

Card* Game::getCardOnField(){ return field.size() == 0 ? nullptr : field.back(); }

Player* Game::getCurrentPlayerTurn(){ return turns.getCurrentTurn(); }

GameState Game::getGameState(){ return state; }

void Game::displayCards(std::vector<Card*> cards){
	for(Card* card : cards)
		std::cout<<card->getValue()<<" of "<<card->getColorString()<<std::endl;
}

void Game::displayPlayerCards(Player* player){
	std::cout<<player->getName()<<"'s cards: \n";
	displayCards(player->getCards());
}
