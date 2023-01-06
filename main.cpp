#include <iostream>

#include "./include/my_sdl.h"
#include "./include/perceptron.h"
#include "./include/my_random.h"

const int32_t WIDTH = 100, HEIGHT = 100, RATIO = 6;

int main ( int argc, char ** argv )
{
	my_sdl msdl ( 600, 600, "Perceptron" );
	perceptron pct ( WIDTH, HEIGHT );
	my_random myran ( 0, 1 );

	bool done = false;
	SDL_Event e;
	while ( !done ) {
		SDL_SetRenderDrawColor ( msdl.renderer, 0, 0, 0, 255);
		SDL_RenderClear(msdl.renderer);
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				switch( e.key.keysym.sym ){
					case SDLK_r:
						pct.learn ( true );
						break;
					case SDLK_c:
						pct.learn ( false );
						break;
					case SDLK_l:
						for ( int i = 0 ; i < 100 ; ++i )
							pct.learn ( bool( myran.get_next() ) );
						break;
					case SDLK_p:
						pct.print_performance ();
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch ( e.button.button ) {
					case SDL_BUTTON_LEFT:
						break;
					default:
						break;
				}
			case SDL_MOUSEMOTION:
				int pos_x, pos_y;
				SDL_GetMouseState ( &pos_x, &pos_y );
				break;
			default: {}
			}
		}
		// SDL_RenderFillRect(SDL_Renderer * renderer, const SDL_Rect * rect);
		pct.draw_layer_sdl ( msdl, RATIO );
		SDL_RenderPresent ( msdl.renderer );
	}

	return 0;
}
