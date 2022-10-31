// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cctype>

#include <unordered_map>
#include <string> // For command input/output

#include "media.h"
#include "videogame.h"
#include "movie.h"
#include "music.h"

#include "command.h"

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
const Media::Var COL_VARS[COL_CT] = { Media::Var::Type, Media::Var::Title, Media::Var::Year,
	 Media::Var::Creator, Media::Var::Rating, Media::Var::Duration, Media::Var::Publisher };
const int COL_WIDTH[COL_CT] = { 12, 20, 4, 20, 6, 9, 20 };
const bool COL_ENABLED[COL_CT] = { false, true, true, true, true, true, true };

Media::Var getMediaVarFromStr(const char* rawstr) {
	auto lowercase = [](char* s) {
		while (*s != '\0') {
			*(s++) = tolower(*s);
		}
	};
	char str[strlen(rawstr)+1];
	strcpy(str, rawstr);
	lowercase(str);
	char lowered[128] = {}; // Column names hopefully aren't longer than 127 characters.
	for (int i=0;i<COL_CT;i++) {
		strcpy(lowered, COL_NAMES[i]);
		lowercase(lowered);
		if (strcmp(lowered, str)) return COL_VARS[i];		
	}
	return Media::Var::NotFound;
}

void printHeader() {
	for (int i=0;i<COL_CT;i++) {
		if (COL_ENABLED[i]) {
			printf(COL_LA[i] ? "%-*.*s " : "%*.*s ", COL_WIDTH[i], COL_WIDTH[i], COL_NAMES[i]);
		}
	}
	printf("\n");
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

void CmdSize(bool &running, std::vector<Media*>& medias, const CommandBuf& cb) {	
	printf("Media Count: %i\n", medias.size());
}

void CmdPrint(bool &running, std::vector<Media*>& medias, const CommandBuf& cb) {	
	printHeader();
	
	for (auto it = medias.cbegin();it!=medias.cend();++it)
	{
		Media* mptr = *it;
		MediaType mt = getType(mptr);
		const char* mts = getMediaTypeStr(mt);
	
		#define STR_COL(idx, cptr) if (COL_ENABLED[idx]) printf("%*.*s ", COL_WIDTH[idx], COL_WIDTH[idx], cptr);	
		STR_COL(0, mts);
		STR_COL(1, mptr->getTitle());
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
		printf("\n");
	}
}

void CmdQuit(bool &running, std::vector<Media*>& medias, const CommandBuf& cb) {
	printf("Quit!\n");
	running = false;
}

void CmdHelp(bool &running, std::vector<Media*>& medias, const CommandBuf& cb);

using CommandFunc = void(*)(bool&, std::vector<Media*>&, const CommandBuf&);

const std::unordered_map<std::string, CommandFunc> cmd_map = {
	{ "quit", CmdQuit },
	{ "print", CmdPrint },
	{ "size", CmdSize },
	{ "help", CmdHelp }
};

void CmdHelp(bool &running, std::vector<Media*>& medias, const CommandBuf& cb) {
	const char* const prefix = "	";
	printf("Help:\n");
	for (auto it = cmd_map.cbegin();it!=cmd_map.cend();++it) {
		printf("%s%s\n",prefix,it->first.c_str());
	}
}

std::string tolowercase(const std::string& old) {
	std::string lowered = old;
	for (auto it=lowered.begin();it!=lowered.end();++it) {
		*it = std::tolower(*it);
	}
	return lowered;
}

const char* const ADDITARGS = "doesn't take additional arguments!";
int main() {
	std::vector<Media*> medias = makeDefaultMedias();
	CommandBuf cb;	

	sort(medias);
	bool running = true;
	while (running) {
		printf("Running!\n");
		cb("> ");
		if (cb.Tokens() < 1) continue;
		std::string cmd = tolowercase(cb.GetToken(0));
		try {
			CommandFunc func = cmd_map.at(cmd);
			func(running,medias,cb);
		} catch (...) { printf("Error encountered!\n"); }	
	}	

	return 0;
}
