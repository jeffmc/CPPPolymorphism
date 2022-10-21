// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream>

#include "types.h"

int main() {
	
	Videogame vg = Videogame("Super Mario 64", 1999, "Nintendo", 5.0f);
	
	Music mu = Music("Hip Hop", 2000, "Dead Prez", "Loud Record LLC");

	Movie mo = Movie("Top Gun", 2022, "Bill Gates", Duration(0, 2,11,0), 4.13f);

	return 0;
}

