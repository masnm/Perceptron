#pragma once

#include <SDL2/SDL.h>
#include <string>

class my_sdl {

	public:
		SDL_Window *window;
		SDL_Renderer *renderer;

	public:
		my_sdl ( int width, int height, std::string name );
		~my_sdl ();
};
