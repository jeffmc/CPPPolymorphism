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

const int COL_CT = 7;
const bool COL_LA[COL_CT]     = {false, false, false, true, false, false, true };
const char* COL_NAMES[COL_CT] = {"Type", "Title", "Year", "Creator", "Rating", "Duration", "Publisher" };
const int COL_WIDTH[COL_CT] = { 12, 20, 4, 20, 6, 9, 20 };
const bool COL_ENABLED[COL_CT] = { false, true, true, true, true, true, true };

void printHeader() {
	printf("|");
	for (int i=0;i<COL_CT;i++) {
		if (COL_ENABLED[i]) {
			printf(COL_LA[i] ? "%-*.*s " : "%*.*s ", COL_WIDTH[i], COL_WIDTH[i], COL_NAMES[i]);
		}
	}
	printf("|\n");
}


int Duration::cmp(const Duration &a, const Duration &b) {
	int hd = a.hours - b.hours;
	if (hd != 0) return hd;
	int md = a.mins - b.mins;
	if (md != 0) return md;
	return a.secs - b.secs;
}
template<typename T>
void vecswap(std::vector<T> &v, const size_t a, const size_t b) {
	T tmp = v[a];
	v[a] = v[b];
	v[b] = tmp;	
};
void sort(std::vector<Media*> &medias) {	
	size_t n = medias.size();
	bool swapped = true;
	size_t swaps = 0;
	while (swapped) {
		swapped = false;
		for (int i=1;i<n;i++) {
			if (Media::cmp(Media::Var::Title, medias[i-1], medias[i])>0) {
				vecswap<Media*>(medias, i-1,i);
				swapped = true;
				swaps++;
			}
		}
	}
 	printf("Using %u swaps, sorted by: \n", swaps);
}


int main() {
	std::vector<Media*> medias = makeDefaultMedias();
	
	sort(medias);

	printf("Media Count: %i\n\n", medias.size());
	printHeader();
	
	for (std::vector<Media*>::iterator it = medias.begin();it!=medias.end();++it)
	{
		Media* mptr = *it;
		MediaType mt = getType(mptr);
		const char* mts = getMediaTypeStr(mt);
		
		#define CELL_EXP(idx, data) COL_WIDTH[idx], COL_WIDTH[idx], data
		//      Type  Ttl   Yr  Cr    Rtg   Dur         Pub
		printf("|");
		if (COL_ENABLED[0]) {
			printf("%*.*s ", COL_WIDTH[0], COL_WIDTH[0], mts);
		}
		if (COL_ENABLED[1]) {
			printf("%*.*s ", COL_WIDTH[1], COL_WIDTH[1], mptr->getTitle());
		}
		if (COL_ENABLED[2]) {
			printf("%*u ", COL_WIDTH[2], *(mptr->getYear()));
		}
		if (COL_ENABLED[3]) {
			const char* str = mptr->getCreator();
			if (str != nullptr) {
				printf("%-*.*s ", COL_WIDTH[3], COL_WIDTH[3], str);
			} else {
				printf("%*c ", COL_WIDTH[3], ' ');
			}
		}
		if (COL_ENABLED[4]) {
			const float* rat = mptr->getRating();
			if (rat != nullptr) {
				printf("%*.*f ", COL_WIDTH[4], 1, *rat);
			} else {
				printf("%*c ", COL_WIDTH[4], ' ');
			}
		}
		if (COL_ENABLED[5]) {
			const Duration* dur = mptr->getDuration();
			if (dur != nullptr) {
				printf("%*u:%0*u:%0*u ", 3, dur->hours, 2, dur->mins, 2, dur->secs);
			} else {
				printf("%*c ", COL_WIDTH[5], ' ');
			}
		}
		if (COL_ENABLED[6]) {
			const char* pub = mptr->getPublisher();
			if (pub != nullptr) {
				printf("%-*.*s ", COL_WIDTH[6], COL_WIDTH[6], pub);
			} else {
				printf("%*c ", COL_WIDTH[6], ' ');
			}
		}
		printf("|\n");
	}

	return 0;
}
