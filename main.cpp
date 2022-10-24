// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream>
#include <vector>

#include "types.h"

int main() {

	std::vector<Media*> mediavec = {
		new Videogame("Super Mario 64", 1999, "Nintendo", 5.0f),
		new Music("Hip Hop", 2000, "Dead Prez", { 0,3,34 },  "Loud Records LLC"),
		new Music("Easily", 1999, "RHC Peppers", { 0,3,51 },  "Warner Records Inc."),
		new Movie("Top Gun", 2022, "Joseph Kosinski", { 2,11,0 }, 4.13f)
	};

	const int BUFSZ = 16;
	char buf[BUFSZ] = {};
	for (std::vector<Media*>::const_iterator it = mediavec.cbegin();
			it != mediavec.cend(); ++it)
	{
		(*it)->printm0(buf,BUFSZ);
		printf("%*s",BUFSZ,buf);
		(*it)->printm1(buf,BUFSZ);
		printf("%*s",BUFSZ,buf);
		(*it)->printm2(buf,BUFSZ);
		printf("%*s",BUFSZ,buf);
		(*it)->printm3(buf,BUFSZ);
		printf("%*s",BUFSZ,buf);
		(*it)->printm4(buf,BUFSZ);
		printf("%*s",BUFSZ,buf);
		(*it)->printm5(buf,BUFSZ);
		printf("%*s",BUFSZ,buf);
		(*it)->printm6(buf,BUFSZ);
		printf("%*s",BUFSZ,buf);
		(*it)->printm7(buf,BUFSZ);
		printf("%*s",BUFSZ,buf);

		printf("\n");
	}
	return 0;
}

