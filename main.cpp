// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <algorithm>

#include <unordered_map> // Pair command keyword with its function pointer.
#include <string> // For command input/output

#include "media.h" // Media types
#include "videogame.h"
#include "movie.h"
#include "music.h"

#include "command.h" // Command buffer, all interaction with console input, and tokenization of the input string.
#include "default.h" // default data

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
struct TableState {
public:
	static const int COL_CT = 7;
	const bool COL_LA[COL_CT]     = {false, false, false, true, false, false, true };
	std::string COL_NAMES[COL_CT] = {"Type", "Title", "Year", "Creator", "Rating", "Duration", "Publisher" };
	const Media::Var COL_VARS[COL_CT] = { Media::Var::Type, Media::Var::Title, Media::Var::Year,
		 Media::Var::Creator, Media::Var::Rating, Media::Var::Duration, Media::Var::Publisher };
	int COL_WIDTH[COL_CT] = { 25, 25, 4, 25, 6, 9, 25 };
	bool COL_ENABLED[COL_CT] = { false, true, true, true, true, true, true };
};

void printHeader(const TableState& ts) {
	for (int i=0;i<ts.COL_CT;i++) {
		if (ts.COL_ENABLED[i]) {
			printf(ts.COL_LA[i] ? "%-*.*s " : "%*.*s ", 
				ts.COL_WIDTH[i], ts.COL_WIDTH[i], ts.COL_NAMES[i].c_str());
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

void printMedias(const TableState& ts, const std::vector<Media*> &medias) {
	for (auto it = medias.cbegin();it!=medias.cend();++it)
	{
		Media* mptr = *it;
		MediaType mt = getType(mptr);
		const char* mts = getMediaTypeStr(mt);
	
		#define STR_COL(idx, cptr) if (ts.COL_ENABLED[idx]) printf("%*.*s ", ts.COL_WIDTH[idx], ts.COL_WIDTH[idx], cptr);	
		STR_COL(0, mts);
		STR_COL(1, mptr->getTitle());
		if (ts.COL_ENABLED[2]) {
			printf("%*u ", ts.COL_WIDTH[2], *(mptr->getYear()));
		}
		if (ts.COL_ENABLED[3]) {
			const char* str = mptr->getCreator();
			if (str != nullptr) {
				printf("%-*.*s ", ts.COL_WIDTH[3], ts.COL_WIDTH[3], str);
			} else {
				printf("%*c ", ts.COL_WIDTH[3], ' ');
			}
		}
		if (ts.COL_ENABLED[4]) {
			const float* rat = mptr->getRating();
			if (rat != nullptr) {
				printf("%*.*f ", ts.COL_WIDTH[4], 1, *rat);
			} else {
				printf("%*c ", ts.COL_WIDTH[4], ' ');
			}
		}
		if (ts.COL_ENABLED[5]) {
			const Duration* dur = mptr->getDuration();
			if (dur != nullptr) {
				printf("%*u:%0*u:%0*u ", 3, dur->hours, 2, dur->mins, 2, dur->secs);
			} else {
				printf("%*c ", ts.COL_WIDTH[5], ' ');
			}
		}
		if (ts.COL_ENABLED[6]) {
			const char* pub = mptr->getPublisher();
			if (pub != nullptr) {
				printf("%-*.*s ", ts.COL_WIDTH[6], ts.COL_WIDTH[6], pub);
			} else {
				printf("%*c ", ts.COL_WIDTH[6], ' ');
			}
		}
		printf("\n");
	}
}

// Commands

struct ProgState {
	TableState ts;
	bool running;
	CommandBuf cb;
	std::vector<Media*>& medias;
};

void CmdSort(ProgState& ps) {	
	if (ps.cb.Tokens() < 2) {
		printf("Need more arguments!\n");
		return;	
	}

	Media::Var sortvar = Media::getVar(ps.cb.GetToken(1));
	if (sortvar == Media::Var::NotFound) {
		printf("\"%s\" not a valid media variable!\n", ps.cb.GetToken(1));
		return;
	}

	size_t n = ps.medias.size();
	bool swapped = true;
	size_t swaps = 0;
	while (swapped) {
		swapped = false;
		for (int i=1;i<n;i++) {
			if (Media::cmp(sortvar, ps.medias[i-1], ps.medias[i])>0) {
				vecswap<Media*>(ps.medias, i-1,i);
				swapped = true;
				swaps++;
			}
		}
	}
 	printf("Using %u swaps, sorted by: %s\n", swaps, ps.cb.GetToken(1)); // TODO: Print var as string, not cmdbuf token
}

void CmdSize(ProgState& ps) {	
	printf("Media Count: %i\n", ps.medias.size());
}

void CmdSearch(ProgState& ps) {
	if (ps.cb.Tokens() < 2) {
		printf("Need a search token!\n");
		return;
	}	
	const char* key = ps.cb.GetToken(1);
	std::vector<Media*> filtered;
	std::copy_if(ps.medias.begin(), ps.medias.end(), std::back_inserter(filtered), 
		[key](Media* m) { return m->search(key); });
	printHeader(ps.ts);
	printMedias(ps.ts, filtered);	
	printf("\nFilter to %u results: \"%s\"\n", filtered.size(), key);
}

void CmdPrint(ProgState& ps) {	
	printHeader(ps.ts);
	printMedias(ps.ts, ps.medias);
}

void CmdQuit(ProgState& ps) {
	printf("Quit!\n");
	ps.running = false;
}

void CmdHelp(ProgState& ps);

using CommandFunc = void(*)(ProgState&);

const std::unordered_map<std::string, CommandFunc> cmd_map = {
	{ "quit", CmdQuit },
	{ "print", CmdPrint },
	{ "size", CmdSize },
	{ "help", CmdHelp },
	{ "sort", CmdSort },
	{ "search", CmdSearch }
};

void CmdHelp(ProgState& ps) {
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
	const std::vector<Media*> full = makeDefaultMedias();
	std::vector<Media*> medias = full;

	ProgState ps = {
		TableState(), true, CommandBuf(), medias
	};

	while (ps.running) {
		ps.cb("> ");
		if (ps.cb.Tokens() < 1) continue;
		std::string cmd = tolowercase(ps.cb.GetToken(0));
		try {
			CommandFunc func = cmd_map.at(cmd);
			func(ps);
		} catch (...) { printf("Error encountered!\n"); }	
	}	

	return 0;
}
