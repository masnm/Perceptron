#include "../include/my_random.h"

my_random::my_random ( int32_t low, int32_t high )
{
	gen32 = std::mt19937 ( rd() );
	distrib = std::uniform_int_distribution<> ( low, high );
}

int32_t my_random::get_next ()
{
	return distrib ( gen32 );
}
