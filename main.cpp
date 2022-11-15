// Jeff McMillan 10-21-2022
// CPP Classes
// This is a user-managed database of information related to different types of media.
// The user can add, search, and delete media from the database (vector). The user may also quit the program.
// In addition to those commands, the user may also print out all media, sort the media by column, toggle column visibility, 

#include <iostream> // console interaction
#include <vector> // storing media pointers
#include <cstdio> // lots
#include <cstdlib> // lots
#include <cctype> // Lowercasing
#include <algorithm> // Manipulation of vectors
#include <iterator> // For Media iterators

#include <unordered_map> // Pair command keyword with its function pointer.
#include <string> // For command input/output, detecting keywords

#include "main.h" // Global function declarations, a few structs.

#include "media.h" // Media definitions 
#include "videogame.h" // Publisher and rating
#include "movie.h" // Creator, duration and rating 
#include "music.h" // Creator, durating and publisher

#include "command.h" // Command buffer, all interaction with console input, and tokenization of the input string.
#include "default.h" // default data

// Return which type of derived type of Media this is pointer to using dynamic_cast
#define TRYRET(PTR, MTYPE) try { MTYPE* tp = dynamic_cast<MTYPE*>(PTR); if (tp!=0) return MediaType::MTYPE; } catch (...) {}
MediaType getMediaTypeFromPtr(Media* m) {
	TRYRET(m, Videogame);
	TRYRET(m, Movie);
	TRYRET(m, Music);
	return MediaType::UnknownType;
}
#undef TRYRET
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

// print out the column titles filling each column width.
void printHeader(const TableState& ts) {
	for (int i=0;i<ts.COL_CT;i++) {
		if (ts.COL_ENABLED[i]) {
			printf(ts.COL_LA[i] ? "%-*.*s " : "%*.*s ", 
				ts.COL_WIDTH[i], ts.COL_WIDTH[i], ts.COL_NAMES[i]);
		}
	}
	printf("\n");
}

// Comparison between Duration instances.
int Duration::cmp(const Duration &a, const Duration &b) {
	int hd = a.hours - b.hours;
	if (hd != 0) return hd;
	int md = a.mins - b.mins;
	if (md != 0) return md;
	return a.secs - b.secs;
}

// Swap two elements at given indices within a vector.
template<typename T> // MAY HAVE TO REMOVE THIS LINE IN ORDER TO COMPILE!
void vecswap(std::vector<T> &v, const size_t a, const size_t b) {
	T tmp = v[a];
	v[a] = v[b];
	v[b] = tmp;	
};

// print a table of medias (doesn't print the header)
void printMedias(const TableState& ts, const std::vector<Media*> &medias) {
	for (auto it = medias.cbegin(); it!=medias.cend(); ++it)
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
void CmdSort(ProgState& ps) { // Sort the media by a given column variable, look at Media::cmp(...)
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

void CmdSize(ProgState& ps) { // Print out the size of media vectors
	printf("Default Media Count: %u\n", ps.originals.size());
	printf("Current Media Count: %u\n", ps.medias.size());
}

// Search the current media array using the specified token, doesn't add/remove any objects from array.
void CmdSearch(ProgState& ps) {
	if (ps.cb.Tokens() < 2) {
		printf("Need a search token!\n");
		return;
	}	
	const char* key = ps.cb.GetToken(1);
	std::vector<Media*> filtered = ps.medias;
	std::remove_if(filtered.begin(), filtered.end(), 
		[key](Media* m) { return (!m->search(key)); });
	printHeader(ps.ts);
	printMedias(ps.ts, filtered);	
	printf("Searching for \"%s\" returned %u results\n", key, filtered.size());
}

// Deallocate the media instances within the vector when
#define DEALLOCANDERASE(conditional) for (auto it = ps.medias.begin();it != ps.medias.end();) { \
			if (conditional){delete(*it);ps.medias.erase(it);}else{++it;}}		
void CmdDelete(ProgState& ps) {
	static const char* const CSVMEDIATYPES = "videogame, movie, music"; 
	if (ps.cb.Tokens() < 2) {
		printf("Expected a mode: \"delete [search/type] [...]\"\n");
		return;
	}
	const char* var = ps.cb.GetToken(1);
	if (strcmp(var,"search")==0) {
		if (ps.cb.Tokens() < 3) {
			printf("Expected a search key: \"delete search [key]\"\n");
			return;
		}
		const char* key = ps.cb.GetToken(2);
		DEALLOCANDERASE((*it)->search(key));
	} else if (strcmp(var,"type")==0) {
		if (ps.cb.Tokens() < 3) {
			printf("Expected a type: \"delete search [type]\" (%s)\n", CSVMEDIATYPES);
			return;
		}
		const char* typestr = ps.cb.GetToken(2);
		const MediaType type = Media::getType(typestr);
		if (type == MediaType::UnknownType) {
			printf("\"%s\" is not a valid media type!\n", typestr);
			return;
		}
		DEALLOCANDERASE(getMediaTypeFromPtr(*it) == type);
	} else {
		printf("\"%s\" not a valid filter variable! (search, type)\n", var);
		return;
	}
	// TODO: Add a confirmation prompt (y/n)
	printf("%u medias remaining\n", ps.medias.size());
}

// Prints out the table header and content for all medias.
void CmdPrint(ProgState& ps) {	
	printHeader(ps.ts);
	printMedias(ps.ts, ps.medias);
}

// Quits program as long as additional arguments aren't accidentally passed.
void CmdQuit(ProgState& ps) {
	if (ps.cb.Tokens() > 1) {
		printf("Didn't expect additional arguments!\n");
		return;
	}
	printf("Quit!\n");
	ps.running = false;
}

// Add different types of media, delegating to the Derived::usercreated() method to instantiate.
void CmdAdd(ProgState& ps) { // TODO: Implement usercreated funcs in media type classes.
	if (ps.cb.Tokens() < 2) {
		printf("Expected a type: \"add [type]\" (videogame, movie, music)\n");
		return;
	} else if (ps.cb.Tokens() > 2) {
		printf("Unexpected additional tokens!\n");
		return;
	}
	MediaType mt = Media::getType(ps.cb.GetToken(1));
	if (mt == MediaType::UnknownType) {
	}	

	Media* mptr;
	switch (mt) {
	case MediaType::Videogame:
		mptr = Videogame::usercreated();
		break;
	case MediaType::Movie:
		mptr = Movie::usercreated();
		break;
	case MediaType::Music:
		mptr = Music::usercreated();
		break;
	default:	
		printf("Couldn't determine \"%s\" as a media type!\n", ps.cb.GetToken(1));
		return;
	}
	printf("Got pointer: %p\n", mptr);
	delete mptr; // TODO: Add to vector instead!
}

void CmdToggle(ProgState& ps) {
	if (ps.cb.Tokens() < 2) {
		printf("Expected a column argument: \" toggle [column]\"\n");
		return;
	}
	const Media::Var mv = Media::getVar(std::string(ps.cb.GetToken(1)));
	if (mv == Media::Var::NotFound) {
		printf("\"%s\" is not a known media type!\n", ps.cb.GetToken(1));
		return;
	}
	for (size_t i=0;i<TableState::COL_CT;i++) {
		if (TableState::COL_VARS[i] == mv) {
			ps.ts.COL_ENABLED[i] = !ps.ts.COL_ENABLED[i];
			printf("Toggled visibility of %s!\n", TableState::COL_NAMES[i]);
			return;
		}
	}
	printf("%s: %s, didn't find what should've been a match!\n", __FILE__, __LINE__);
} 

void CmdEnableCols(ProgState& ps) {
	for (size_t i=0;i<TableState::COL_CT;i++) ps.ts.COL_ENABLED[i] = true;
	printf("All columns visible!\n");
}

// Restore media vector to a copy of instances in the original vector (uses copy constructor).
// Also calls CmdEnableCols()
void CmdDefault(ProgState& ps) {
	ps.medias.clear();
	ps.medias.reserve(ps.originals.size());

// Cast to a derived type, run the derived class' copy constructor and insert the copied instance into the new media vector.
#define TRYCOPY(BASEPTR, DERIVED) try { const DERIVED* DERIVED##_ptr = dynamic_cast<DERIVED*>(BASEPTR); \
if ( DERIVED##_ptr !=0 ) { \
	ps.medias.push_back( new DERIVED(*( DERIVED##_ptr )) ); \
	continue; \
} } catch (...) {} 

	for (auto it = ps.originals.begin(); it != ps.originals.end(); ++it) {
		Media* mptr = *it;
		TRYCOPY(mptr, Videogame);
		TRYCOPY(mptr, Music);
		TRYCOPY(mptr, Movie);
	}
#undef TRYCOPY
	
	printf("Media reset to default %u elements!\n", ps.medias.size());
	CmdEnableCols(ps);
}

// Clear all medias (TODO: Implement as wildcard * in delete command!)
void CmdClear(ProgState& ps) {
	ps.medias.clear();
	printf("Medias cleared, %u elements!\n", ps.medias.size());
}

const std::unordered_map<std::string, CommandDefinition> cmd_map = { // keys are commands for user
	{       "quit", { CmdQuit, "", "Ends the program." }},
	{      "print", { CmdPrint, "", "Lists all the media." }},
	{       "size", { CmdSize, "", "Prints out the size of default media and current media groups." }},
	{       "help", { CmdHelp, "", "this" }},
	{       "sort", { CmdSort, "[var]", "Sorts the media by the given variable (type, title, year...) (Ascending)" }},
	{     "search", { CmdSearch, "[keyword]", "Search through media for given keyword." }},
	{     "delete", { CmdDelete, "[mode] [keyword]", "Remove media matching the given (type, search) and (type/keyword) pair." }}, 
	{    "default", { CmdDefault, "", "Resets media back to default. Deletes new entries and restores removed defaults. Also enables visibility of all columns." }},
	{        "add", { CmdAdd, "[type]", "Add media of specified type, will prompt for properties and preview." }}, 
	{     "toggle", { CmdToggle, "[column]", "Toggle the visibility of specified column."}},
	{ "enablecols", { CmdEnableCols, "", "Enables visibility of all columns."}},
	{      "clear", { CmdClear, "", "Clears the media list. Removes all medias." }},
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

// TODO: DESTROY THIS FUNCTION OR REWRITE FOR CSTRINGS!!!
// Return a string that is lowercase.
std::string tolowercase(const std::string& old) {
	std::string lowered = old;
	for (auto it=lowered.begin();it!=lowered.end();++it) {
		*it = std::tolower(*it);
	}
	return lowered;
}

int main() {
	// Instantiate default TableState, program is running, default CommandBuf, default originals, and blank currents.
	ProgState ps = { // Since all command functions receive same arguments, this is the single common arg.
		TableState(), true, CommandBuf(), makeDefaultMedias(), {}
	};

	while (ps.running) { // Keep prompting for commands as long as user hasn't ended program/
		ps.cb("> "); // Prompt user for input
		if (ps.cb.Tokens() < 1) continue; // If no tokens are passed, skip loop.
		std::string cmd = tolowercase(ps.cb.GetToken(0)); // Commands are case-INSENSITIVE.
		try { // Try to find the user's command!
			CommandDefinition::Function func = cmd_map.at(cmd).func; // Find command function from key.
			func(ps); // Call found function using the current ProgState 
		} catch (...) { printf("\"%s\" is not a known command!\n", ps.cb.GetToken(0)); } // When key is not found in map.
	}	

	return 0;
}
