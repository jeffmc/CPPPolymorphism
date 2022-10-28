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

#include "default.h"

#define TRYRET(PTR, MTYPE) try { MTYPE* tp = dynamic_cast<MTYPE*>(PTR); if (tp!=0) return MediaType::MTYPE; } catch (...) {}
MediaType getType(Media* m) {
	TRYRET(m, Videogame);
	TRYRET(m, Movie);
	TRYRET(m, Music);
	return MediaType::UnknownType;
}
#undef TRYRETCATCH
#define CASERET(MTYPE) case MediaType::MTYPE: return #MTYPE;
const char* getMediaTypeStr(const MediaType &mt) {
	switch (mt) {
	CASERET(Videogame);
	CASERET(Movie);
	CASERET(Music);
	CASERET(UnknownType);
	default: return "INVALID ENUM VALUE!";		
	}
}
#undef CASERET

const char* COL_NAMES[7] = {"Type", "Title", "Year", "Creator", "Rating", "Duration", "Publisher" };
const int COL_WIDTH[7] = { 12, 20, 4, 20, 6, 9, 20 };
const bool COL_ENABLED[7] = { true, true, true, true, true, true, true };

#define COL_EXP(idx) COL_WIDTH[idx], COL_WIDTH[idx], COL_NAMES[idx]
void printHeader() {
	printf("%*.*s %*.*s %*.*s %*.*s %*.*s %*.*s %*.*s\n",
		COL_EXP(0),COL_EXP(1),COL_EXP(2),COL_EXP(3),
		COL_EXP(4),COL_EXP(5),COL_EXP(6));
}
#undef COL_EXP


int main() {
	std::vector<Media*> medias = makeDefaultMedias();

	printf("Media Count: %i\n\n", medias.size());
	printHeader();
	
	for (std::vector<Media*>::iterator it = medias.begin();it!=medias.end();++it)
	{
		Media* mptr = *it;
		MediaType mt = getType(mptr);
		const char* mts = getMediaTypeStr(mt);
		
		#define CELL_EXP(idx, data) COL_WIDTH[idx], COL_WIDTH[idx], data
		//      Type  Ttl   Yr  Cr    Rtg   Dur         Pub
		printf("%*.*s %*.*s %*u %*.*s %*.*f %*u:%*u:%*u %*.*s\n",
			CELL_EXP(0,mts),CELL_EXP(1,mptr->getTitle()),COL_WIDTH[2], *(mptr->getYear()),
			CELL_EXP(3,mptr->getCreator()), COL_WIDTH[4], 1, *(mptr->getRating()),
			3, mptr->getDuration()->hours,2, mptr->getDuration()->mins,2, mptr->getDuration()->secs,
			CELL_EXP(6,mptr->getPublisher()));
			
	}

	return 0;
}
