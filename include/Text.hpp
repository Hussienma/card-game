#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "RenderWindow.hpp"

class Text {
	private:
	RenderWindow* window;
	TTF_Font* font;
	SDL_Surface* textSurface;
	
	public:
	SDL_Texture* texture;
	SDL_Rect position;
	Text();
	Text(RenderWindow* window, SDL_Color color, std::string text, std::string fontFamily, int fontSize, int posX, int posY): window(window){
		std::string fontPath = "./fonts/"+ fontFamily +".ttf";
		font = TTF_OpenFont(fontPath.c_str(), fontSize);
		if(!font){
			std::cerr<<"Error loading font "<<SDL_GetError()<<std::endl;
		}

		textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		if(!textSurface){
			std::cerr<<"Failed to create text surface.\n";
		}
		texture = window->loadTextureFromSurface(textSurface);

		TTF_SizeText(font, text.c_str(), &position.w, &position.h);
		position.x = posX - position.w/2;
		position.y = posY - position.h/2;
	}
	~Text(){
		SDL_FreeSurface(textSurface);
		TTF_CloseFont(font);
	}

	void render(){
		window->render(texture, position);
	}
};
