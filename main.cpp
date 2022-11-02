// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream> // console interaction
#include <vector> // storing media pointers
#include <cstdio> // lots
#include <cstdlib> // lots
#include <cctype> // Lowercasing
#include <algorithm> // Manipulation of vectors

#include <unordered_map> // Pair command keyword with its function pointer.
#include <string> // For command input/output, detecting keywords

#include "media.h" // Media definitions 
#include "videogame.h" // Publisher and rating
#include "movie.h" // Creator, duration and rating 
#include "music.h" // Creator, durating and publisher

#include "command.h" // Command buffer, all interaction with console input, and tokenization of the input string.
#include "default.h" // default data

#define TRYRET(PTR, MTYPE) try { MTYPE* tp = dynamic_cast<MTYPE*>(PTR); if (tp!=0) return MediaType::MTYPE; } catch (...) {}
MediaType getMediaTypeFromPtr(Media* m) {
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
		MediaType mt = getMediaTypeFromPtr(mptr);
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
	const std::vector<Media*>& originals;
	std::vector<Media*>& medias; // could be a filtered version
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
	printf("Total Media Count: %i\n", ps.originals.size());
	printf("Filtered Media Count: %i\n", ps.medias.size());
}

// Search within medias (filtered)
void CmdSearch(ProgState& ps) {
	if (ps.cb.Tokens() < 2) {
		printf("Need a search token!\n");
		return;
	}	
	const char* key = ps.cb.GetToken(1);
	std::vector<Media*> filtered = ps.medias;
	std::remove_if(filtered.begin(), filtered.end(), 
		[key](Media* m) { return m->search(key); });
	printHeader(ps.ts);
	printMedias(ps.ts, filtered);	
	printf("Searching for \"%s\" returned %u results\n", key, filtered.size());
}

void CmdReset(ProgState& ps) {
	ps.medias = ps.originals;
	printf("Media filter reset to %u elements!\n", ps.medias.size());
}

void CmdFilter(ProgState& ps) {
	if (ps.cb.Tokens() < 3) {
		printf("Need a filter token!\n");
		return;
	}
	const char* var = ps.cb.GetToken(1);
	if (strcmp(var,"search")==0) {
		const char* key = ps.cb.GetToken(2);
		auto it = std::remove_if(ps.medias.begin(), ps.medias.end(), // Rearranges non matched to end of vec.
			[key](Media* m) { return !(m->search(key)); });
		ps.medias.erase(it, ps.medias.end()); // Erase leftover elements
	} else if (strcmp(var,"type")==0) {
		const char* typestr = ps.cb.GetToken(2);
		const MediaType type = Media::getType(typestr);
		if (type == MediaType::UnknownType) {
			printf("\"%s\" is not a valid media type!", typestr);
			return;
		}
		auto it = std::remove_if(ps.medias.begin(), ps.medias.end(), 
			[type](Media* m) { return getMediaTypeFromPtr(m) != type; });
		ps.medias.erase(it, ps.medias.end());
	} else {
		printf("\"%s\" not a valid filter variable!", var);
		return;
	}
	//printHeader(ps.ts);
	//printMedias(ps.ts, ps.medias);	
	printf("Filtered to %u results: \"%s\" & \"%s\"\n", ps.medias.size(), var, ps.cb.GetToken(2));
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
struct CommandDefinition {
	using Function = void(*)(ProgState&);
	const Function func;
	const std::string args;
	const std::string help;	
};

const std::unordered_map<std::string, CommandDefinition> cmd_map = {
	{ "quit", { CmdQuit, "", "Ends the program." }},
	{ "print", { CmdPrint, "", "Lists all the media within the current filter." }},
	{ "size", { CmdSize, "", "Prints out the size of original media and filtered media groups." }},
	{ "help", { CmdHelp, "", "this" }},
	{ "sort", { CmdSort, "[var]", "Sorts the filtered media by the given variable (type, title, year...) (Ascending)" }},
	{ "search", { CmdSearch, "[keyword]", "Search through filtered media for given keyword." }},
	{ "filter", { CmdFilter, "[mode] [keyword]",
		 "Filter the media using the given mode (type, search) and type/keyword pair." }}, 
	{ "reset", { CmdReset, "", "Resets all filters, back to original data." }},
};

void CmdHelp(ProgState& ps) {
	const char* const prefix = "	";
	printf("Help:\n");
	size_t maxlen = 0; // strlen(cmd) + 1 + strlen(args)
	for (auto it = cmd_map.cbegin();it!=cmd_map.cend();++it) {
		size_t len = it->first.length() + 1 + it->second.args.length();
		if (len > maxlen) maxlen = len;
	}
	char cmddef[maxlen+1]; // allow for null terminating char
	for (auto it = cmd_map.cbegin();it!=cmd_map.cend();++it) {
		const std::string& args = it->second.args;
		snprintf(cmddef, maxlen+1, args.length()<1 ? "%s":"%s %s", it->first.c_str(), args.c_str());
		printf("%*s - %s\n", maxlen, cmddef, it->second.help.c_str());
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
		TableState(), true, CommandBuf(), full, medias
	};

	while (ps.running) {
		ps.cb("> ");
		if (ps.cb.Tokens() < 1) continue;
		std::string cmd = tolowercase(ps.cb.GetToken(0));
		try {
			CommandDefinition::Function func = cmd_map.at(cmd).func;
			func(ps);
		} catch (...) { printf("Error encountered!\n"); }	
	}	

	return 0;
}
