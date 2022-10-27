// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "media.h"
#include "videogame.h"
#include "movie.h"
#include "music.h"

#define TRYRETCATCH(PTR, MTYPE) try { MTYPE* tp = dynamic_cast<MTYPE*>(PTR); if (tp!=0) return MediaType::MTYPE; } catch (...) {}
MediaType getType(Media* m) {
	TRYRETCATCH(m, Videogame);
	TRYRETCATCH(m, Movie);
	TRYRETCATCH(m, Music);
	return MediaType::UnknownType;
}
#undef TRYRETCATCH
#define CASERET(MTYPE) case MediaType::MTYPE: return #MTYPE;
const char* getTypeStr(const MediaType &mt) {
	switch (mt) {
	CASERET(Videogame);
	CASERET(Movie);
	CASERET(Music);
	CASERET(UnknownType);
	default: return "INVALID ENUM VALUE!";		
	}
}
#undef CASERET

int main() {
	std::vector<Media*> medias = {
		new Videogame("Super Mario 64", 1999, "Nintendo", 5.0f),
		new Music("Hip Hop", 2000, "Dead Prez", Duration(0,3,54),  "Loud Record LLC"),
		new Movie("Top Gun", 2022, "Bill Gates", Duration(2,11,0), 4.13f),
	};

	printf("Media Count: %i\n", medias.size());

	const int headw = 11;
	printf("%*s%*c", headw, "Media Type", Media::COL_SPACING, ' ');
	Media::printHeader();
	printf("\nHere!\n");

	for (std::vector<Media*>::iterator it = medias.begin();it!=medias.end();++it)
	{
		Media* mptr = *it;
		printf("%p\n", mptr);
		MediaType mt = getType(mptr);
	
		// THIS IS CRASHING PROGRAM SILENTLY!!!	
		//printf("%*s%*c", headw, mt, Media::COL_SPACING, ' ');
		
		mptr->print();
	}
	printf("Finished!\n");

	return 0;
}
