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
}
