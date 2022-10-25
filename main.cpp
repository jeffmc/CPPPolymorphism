// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "videogame.h"
#include "movie.h"
#include "music.h"

int main() {
	std::vector<Media*> medias = {
		new Videogame("Super Mario 64", 1999, "Nintendo", 5.0f),
		new Music("Hip Hop", 2000, "Dead Prez", Duration(0,3,54),  "Loud Record LLC"),
		new Movie("Top Gun", 2022, "Bill Gates", Duration(2,11,0), 4.13f),
	};

	for (std::vector<Media*>::iterator it = medias.begin();it!=medias.end();++it)
	{
		Media* mptr = *it;
		try {
			Videogame* vg = dynamic_cast<Videogame*>(mptr);
			if (vg != 0) {
				std::cout << "videogame" << std::endl;
				continue;
			}
		} catch (...) {}
		try {
			Movie* mo = dynamic_cast<Movie*>(mptr);
			if (mo != 0) {
				std::cout << "movie" << std::endl;
				continue;
			}
		} catch (...) {}
		try {
			Music* mu = dynamic_cast<Music*>(mptr);
			if (mu != 0) {
				std::cout << "music" << std::endl;
				continue;
			}
		} catch (...) {}
		std::cout << "unhandled type!" << std::endl;
	}

	return 0;
}
