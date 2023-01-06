#pragma once

#include <vector>

#include "../include/my_sdl.h"

class perceptron {

	public:
		std::vector<std::vector<int32_t>> layer;
		std::vector<std::vector<int32_t>> sample;
		int32_t row, col;
		// min must be negative and max must be positive
		const int32_t WIDTH_MIN = -10, WIDTH_MAX = 10;

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
		void print_performance ( void );

	public:
		void learn ( bool option );
};
