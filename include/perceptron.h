#pragma once

#include <vector>
#include <limits>

#include "../include/my_sdl.h"
#include "../include/my_random.h"

class perceptron {

	private:
		std::vector<std::vector<int32_t>> sample;
		// min must be negative and max must be positive
		const int32_t WIDTH_MIN = -10, WIDTH_MAX = 10;
		my_random myran = my_random ( 0, std::numeric_limits<int32_t>::max() );

	public:
		std::vector<std::vector<int32_t>> layer;
		int32_t row, col;

	public:
		perceptron ( int32_t _row, int32_t _col, int32_t initital = 0 );

	private:
		void sample_rectengle ( void );
		void sample_circle ( void );

	private:
		void clear_sample ( void );
		void learn_rectangle ( void );
		void learn_circle ( void );
		bool predict_sample ( void );

	public:
		void draw_layer_sdl ( my_sdl& msdl, int32_t ratio );
		void draw_sample_sdl ( my_sdl& msdl, int32_t ratio );
		void print_performance ( void );

	public:
		void learn ( bool option );
};
