#include <utility>
#include <iostream>
#include <algorithm>

#include "../include/perceptron.h"

perceptron::perceptron ( int32_t _row, int32_t _col, int32_t initital )
{
	layer.clear();
	layer.resize ( _row );
	for ( auto& row : layer ) {
		row.resize ( _col );
		fill ( row.begin(), row.end(), initital );
	}
	sample.resize ( _row );
	for ( auto& row : sample )
		row.resize ( _col );
	row = _row; col = _col;
}

void perceptron::sample_rectengle ( void )
{
	std::pair<int32_t, int32_t> tl, br;
	tl.first = myran.get_next() % row; br.first = myran.get_next() % row;
	if ( tl.first > br.first ) std::swap ( tl.first, br.first );
	tl.second = myran.get_next() % col; br.second = myran.get_next() % col;
	if ( tl.second > br.second ) std::swap ( tl.second, br.second );

	clear_sample ();
	for ( int32_t i = tl.first ; i < br.first ; ++i )
		for ( int32_t j = tl.second ; j < br.second ; ++j )
			sample[i][j] = 1;
}

void perceptron::sample_circle ( void )
{
	std::pair<int32_t, int32_t> center ( myran.get_next()%row, myran.get_next()%col );

	int32_t min_dis = std::min ( center.first, center.second );
	min_dis = std::min ( min_dis, row - center.first - 1 );
	min_dis = std::min ( min_dis, col - center.second - 1 );
	if ( min_dis < 1 ) min_dis = 1;
	int32_t radious = rand () % min_dis;

	clear_sample ();
	for ( int32_t i = -radious ; i <= radious ; ++i )
		for ( int32_t j = - radious ; j <= radious ; ++j )
			if ( ((i*i) + (j*j)) <= (radious*radious) )
				sample[i + center.first][j + center.second] = 1;

}

void perceptron::clear_sample ( void )
{
	for ( auto& _row : sample )
		for ( auto& _col : _row )
			_col = 0;
}

void perceptron::learn_rectangle ( void )
{
	sample_rectengle ();
	if ( predict_sample() == true ) {
		for ( int32_t i = 0 ; i < row ; ++i )
			for ( int32_t j = 0 ; j < col ; ++j ) {
				layer[i][j] -= sample[i][j];
				std::clamp ( layer[i][j], WIDTH_MIN, WIDTH_MAX );
			}
	}
}

void perceptron::learn_circle ( void )
{
	sample_circle ();
	if ( predict_sample() == false ) {
		for ( int32_t i = 0 ; i < row ; ++i )
			for ( int32_t j = 0 ; j < col ; ++j ) {
				layer[i][j] += sample[i][j];
				std::clamp ( layer[i][j], WIDTH_MIN, WIDTH_MAX );
			}
	}
}

bool perceptron::predict_sample ( void )
{
	int64_t sum = 0;
	for ( int32_t i = 0 ; i < row ; ++i )
		for ( int32_t j = 0 ; j < col ; ++j )
			sum += sample[i][j] * layer[i][j];
	return ( sum >= 0 );
}

void perceptron::draw_layer_sdl ( my_sdl& msdl, int32_t ratio )
{
	auto get_positive= [this]( int32_t val ) {
		return val + abs ( WIDTH_MIN );
	};
	SDL_Rect rect;
	float max_val = abs ( WIDTH_MIN ) + abs ( WIDTH_MAX );
	rect.w = rect.h = ratio;
	for ( int32_t i = 0 ; i < row ; ++i )
		for ( int32_t j = 0 ; j < col ; ++j ) {
			float val = get_positive ( layer[i][j] );
			float red = val / max_val;
			SDL_SetRenderDrawColor ( msdl.renderer, int(red * 255), 0, 0, 255 );
			rect.x = i * ratio; rect.y = j*ratio;
			// SDL_RenderDrawRect(SDL_Renderer * renderer, const SDL_Rect * rect);
			SDL_RenderFillRects ( msdl.renderer, &rect, 1 );
		}
}

void perceptron::draw_sample_sdl ( my_sdl& msdl, int32_t ratio )
{
	auto get_positive= [this]( int32_t val ) {
		return val + abs ( WIDTH_MIN );
	};
	SDL_Rect rect;
	float max_val = abs ( WIDTH_MIN ) + abs ( WIDTH_MAX );
	rect.w = rect.h = ratio;
	for ( int32_t i = 0 ; i < row ; ++i )
		for ( int32_t j = 0 ; j < col ; ++j ) {
			float val = get_positive ( sample[i][j] );
			float red = val / max_val;
			SDL_SetRenderDrawColor ( msdl.renderer, int(red * 255), 0, 0, 255 );
			rect.x = i * ratio; rect.y = j*ratio;
			// SDL_RenderDrawRect(SDL_Renderer * renderer, const SDL_Rect * rect);
			SDL_RenderFillRects ( msdl.renderer, &rect, 1 );
		}
}

void perceptron::print_performance ( void )
{
	int32_t accurate = 0;
	for ( int32_t i = 0 ; i < 100 ; ++i ) {
		bool expected = bool ( myran.get_next() % 2 );
		if ( expected ) sample_circle ();
		else sample_rectengle ();
		if ( predict_sample () == expected ) ++accurate;
	}
	std::cerr << "Accuracy is : " << accurate << "%" << std::endl;
}

void perceptron::learn ( bool option )
{
	if ( option == true ) learn_circle ();
	else learn_rectangle ();
}
