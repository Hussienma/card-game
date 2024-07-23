#pragma once

#include <SDL2/SDL.h>

namespace utils{
	inline float hireTimeInSeconds(){
		float t = SDL_GetTicks();
		t *= 0.001;
		return t;
	}
	
	inline float lerp(float a, float b, float t){
		float x = a+(b-a)*t;
		return x;
	}	
	
	inline float easeIn(float t){
		return t*t;
	}
	
	inline float flip(float x){
		return 1-x;
	}

	inline float easeOut(float t){
		return flip(easeIn(flip(t)));
	}

	inline float easeInOut(float t){
		return lerp(easeIn(t), easeOut(t), t);
	}
}
