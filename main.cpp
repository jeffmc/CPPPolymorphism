// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream>
#include <vector>

#include "types.h"

int main() {

	std::vector<Media*> mediavec = {};

	mediavec.push_back(
		new Videogame("Super Mario 64", 1999, "Nintendo", 5.0f)
	);
	mediavec.push_back(
		new Music("Hip Hop", 2000, "Dead Prez", { 0,3,34 },  "Loud Records LLC")
	);
	mediavec.push_back(
		new Music("Easily", 1999, "RHC Peppers", { 0,3,51 },  "Warner Records Inc.")
	);
	mediavec.push_back(
		new Movie("Top Gun", 2022, "Joseph Kosinski", { 2,11,0 }, 4.13f)
	);
	for (std::vector<Media*>::const_iterator it = mediavec.cbegin();
			it != mediavec.cend(); ++it)
	{
		(*it)->print();
	}
	return 0;
}

