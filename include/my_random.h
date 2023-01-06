#pragma once

#include <random>

class my_random {
	private:
		std::random_device rd;
		std::mt19937 gen32;
		std::uniform_int_distribution<> distrib;
	public:
		my_random ( int32_t low, int32_t high );

	public:
		int32_t get_next ();

};
