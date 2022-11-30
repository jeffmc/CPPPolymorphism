// Jeff McMillan 10-21-2022
// CPP Classes
// This is a user-managed database of information related to different types of media.
// The user can add, search, and delete media from the database (vector). The user may also quit the program.
// In addition to those commands, the user may also print out all media, sort the media by column, toggle column visibility, 
#include <vector> // storing media pointers
#include <cstdio> // lots
#include <cstdlib> // lots
#include <algorithm> // Manipulation of vectors
#include <iterator> // For Media iterators

#include <unordered_map> // Pair command keyword with its function pointer.

#include "main.h" // Global function declarations, a few structs.

#include "media.h" // Media definitions 
#include "videogame.h" // Publisher and rating
#include "movie.h" // Creator, duration and rating 
#include "music.h" // Creator, durating and publisher

#include "command.h" // Command buffer, all interaction with console input, and tokenization of the input string.
#include "default.h" // default data

// Return which type of derived type of Media this is pointer to using dynamic_cast
#define TRYRET(PTR, MTYPE) try { const MTYPE* tp = dynamic_cast<const MTYPE*>(PTR); if (tp!=0) return MediaType::MTYPE; } catch (...) {}
MediaType getMediaTypeFromPtr(const Media* m) {
	TRYRET(m, Videogame);
	TRYRET(m, Movie);
	TRYRET(m, Music);
	return MediaType::UnknownType;
}
#undef TRYRET
#define CASERET(MTYPE) case MediaType::MTYPE: return #MTYPE;
const char* getMediaTypeStr(const MediaType &mt) { // TODO: Replace this code wiht unordered_map!
	switch (mt) {
	CASERET(Videogame);
	CASERET(Movie);
	CASERET(Music);
	CASERET(UnknownType);
	default: return "INVALID ENUM VALUE!";		
	}
}
#undef CASERET

// Comparison between Duration instances.
int Duration::cmp(const Duration &a, const Duration &b) {
	int hd = a.hours - b.hours;
	if (hd != 0) return hd;
	int md = a.mins - b.mins;
	if (md != 0) return md;
	return a.secs - b.secs;
}

// Swap two elements at given indices within a vector.
template<typename T> 
void vecswap(std::vector<T> &v, const size_t a, const size_t b) {
	T tmp = v[a];
	v[a] = v[b];
	v[b] = tmp;	
};

static const char* const DIV = " | ";
// print out the column titles filling each column width.
void printHeader(const TableState& ts) {
	for (int i=0;i<ts.COL_CT;i++) {
		if (ts.COL_ENABLED[i]) {
			printf(ts.COL_LA[i] ? "%-*.*s%s" : "%*.*s%s", 
				ts.COL_WIDTH[i], ts.COL_WIDTH[i], ts.COL_NAMES[i], DIV);
		}
	}
	printf("\n");
}

// print a table of medias (doesn't print the header)
void printMedias(const TableState& ts, const std::vector<Media*> &medias) {
	for (auto it = medias.cbegin(); it!=medias.cend(); ++it)
	{	
		printMedia(ts, *it);
	}
}

void printMedia(const TableState& ts, const Media* mptr) {
	//Media* mptr = *it;
	MediaType mt = getMediaTypeFromPtr(mptr);
	const char* mts = getMediaTypeStr(mt);


	#define STR_COL(idx, cptr) if (ts.COL_ENABLED[idx]) printf("%*.*s%s", ts.COL_WIDTH[idx], ts.COL_WIDTH[idx], cptr, DIV);
	STR_COL(0, mts);
	STR_COL(1, mptr->getTitle());
	if (ts.COL_ENABLED[2]) {
		printf("%*u%s", ts.COL_WIDTH[2], *(mptr->getYear()), DIV);
	}
	if (ts.COL_ENABLED[3]) {
		const char* str = mptr->getCreator();
		if (str != nullptr) {
			printf("%-*.*s%s", ts.COL_WIDTH[3], ts.COL_WIDTH[3], str, DIV);
		} else {
			printf("%*c%s", ts.COL_WIDTH[3], ' ', DIV);
		}
	}
	if (ts.COL_ENABLED[4]) {
		const float* rat = mptr->getRating();
		if (rat != nullptr) {
			printf("%*.*f%s", ts.COL_WIDTH[4], 1, *rat, DIV);
		} else {
			printf("%*c%s", ts.COL_WIDTH[4], ' ', DIV);
		}
	}
	if (ts.COL_ENABLED[5]) {
		const Duration* dur = mptr->getDuration();
		if (dur != nullptr) {
			printf("%*u:%0*u:%0*u%s", 3, dur->hours, 2, dur->mins, 2, dur->secs, DIV);
		} else {
			printf("%*c%s", ts.COL_WIDTH[5], ' ', DIV);
		}
	}
	if (ts.COL_ENABLED[6]) {
		const char* pub = mptr->getPublisher();
		if (pub != nullptr) {
			printf("%-*.*s%s", ts.COL_WIDTH[6], ts.COL_WIDTH[6], pub, DIV); // TODO: Add DIV if I add another column of data
		} else {
			printf("%*c%s", ts.COL_WIDTH[6], ' ', DIV);
		}
	}
	printf("\n");	
}

namespace Command {
	void Sort(ProgState& ps) { // Sort the media by a given column variable, look at Media::cmp(...)
		if (ps.cb.Tokens() < 2) {
			printf("\"sort [variable]\": expected a sort variable!\n");
			return;	
		}

		Media::Var sortvar = Media::getVar(ps.cb.GetLowerToken(1));
		if (sortvar == Media::Var::NotFound) {
			printf("\"%s\" not a valid media variable!\n", ps.cb.GetToken(1));
			return;
		} else if (sortvar == Media::Var::Type) {
			printf("Have not implemented sorting by media type!\n");
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

	void Size(ProgState& ps) { // Print out the size of media vectors
		printf("Default Media Count: %u\n", ps.originals.size());
		printf("Current Media Count: %u\n", ps.medias.size());
	}

	// Search the current media array using the specified token, doesn't add/remove any objects from array.
	void Search(ProgState& ps) {
		if (ps.cb.Tokens() < 2) {
			printf("Need a search token!\n");
			return;
		}	
		const char* key = ps.cb.GetToken(1);
		std::vector<Media*> filtered = ps.medias;
		auto iter = std::remove_if(filtered.begin(), filtered.end(), 
			[key](Media* m) { return !(m->search(key)); });
		filtered.erase(iter, filtered.end());
		printHeader(ps.ts);
		printMedias(ps.ts, filtered);	
		printf("Searching for \"%s\" returned %u results\n", key, filtered.size());
	}

	// Deallocate and remove from vector any media that matches the given query.
	void Delete(ProgState& ps) {
		static const char* const CSVMEDIATYPES = "videogame, movie, music"; // TODO: Create this cstring programmatically 
		if (ps.cb.Tokens() < 2) {
			printf("Expected a mode: \"delete [*/search/type] [...]\"\n");
			return;
		}
		
		std::vector<size_t> cutting_block = {}; // index of medias that match given deletion query.
		const char* var = ps.cb.GetLowerToken(1);
		if (strcmp(var,"*")==0) {
			if (ps.cb.Tokens() != 2) {
				printf("Wildcard doesn't allow additional arguments!\n");
				return;
			}
			for (size_t i=0;i<ps.medias.size();i++) cutting_block.push_back(i);
		} else if (strcmp(var,"search")==0) {
			if (ps.cb.Tokens() != 3) {
				printf("Expected a single-word search key: \"delete search [key]\"\n");
				return;
			}
			const char* key = ps.cb.GetToken(2);
			for (size_t i=0;i<ps.medias.size();i++) {
				if (ps.medias.at(i)->search(key)) cutting_block.push_back(i);
			}
		} else if (strcmp(var,"type")==0) {
			if (ps.cb.Tokens() != 3) {
				printf("Expected a type: \"delete search [type]\" (%s)\n", CSVMEDIATYPES);
				return;
			}
			const char* typestr = ps.cb.GetLowerToken(2);
			const MediaType type = Media::getType(typestr);
			if (type == MediaType::UnknownType) {
				printf("\"%s\" is not a valid media type!\n", typestr);
				return;
			}
			for (size_t i=0;i<ps.medias.size();i++) {
				if (getMediaTypeFromPtr(ps.medias.at(i)) == type) cutting_block.push_back(i);
			}
		} else {
			printf("\"%s\" not a valid filter variable! (search, type)\n", var);
			return;
		}

		printHeader(ps.ts);
		for (auto it = cutting_block.cbegin();it!=cutting_block.cend();it++) {
			printMedia(ps.ts, ps.medias.at(*it));	
		}

		const size_t BUFSIZE = 16;
		char response[BUFSIZE];
		bool trying = true, deleteEntries = false;
		while (trying) {
			printf("Confirm deletion of %u entries above? (y/n)", cutting_block.size());
			CSTR_GETLINE(response,BUFSIZE);
			char* ptr = response;
			while (*ptr) { *ptr = tolower(*ptr); ++ptr; }
			if (strcmp(response,"y")==0) {
				deleteEntries = true;
				trying = false;
			} else if (strcmp(response,"n")==0) {
				deleteEntries = false;
				trying = false;
			} else {
				printf("Invalid response!\n");
				trying = true;
			}
		}
		if (deleteEntries) {
			// reverse iterator so that indices are not affect as deletions are made.
			for (auto crit=cutting_block.crbegin();crit!=cutting_block.crend();++crit) {
				delete ps.medias.at(*crit);
				ps.medias.erase(ps.medias.begin() + *crit);
			}
		} else {
			printf("Did not delete any media\n");
		}

		printf("%u medias remaining\n", ps.medias.size());
	}

	// Prints out the table header and content for all medias.
	void Print(ProgState& ps) {	
		printHeader(ps.ts);
		printMedias(ps.ts, ps.medias);
	}

	// Quits program as long as additional arguments aren't accidentally passed.
	void Quit(ProgState& ps) {
		if (ps.cb.Tokens() > 1) {
			printf("Didn't expect additional arguments!\n");
			return;
		}
		printf("Quit!\n");
		ps.running = false;
	}

	// Add different types of media, delegating to the Derived::usercreated() method to instantiate.
	void Add(ProgState& ps) { // TODO: Implement usercreated funcs in media type classes.
		if (ps.cb.Tokens() < 2) {
			printf("Expected a type: \"add [type]\" (videogame, movie, music)\n");
			return;
		} else if (ps.cb.Tokens() > 2) {
			printf("Unexpected additional tokens!\n");
			return;
		}
		MediaType mt = Media::getType(ps.cb.GetLowerToken(1));
		if (mt == MediaType::UnknownType) {
			printf("Couldn't determine \"%s\" as a media type!\n", ps.cb.GetToken(1));
			return;
		}	

		Media* mptr;
#define MEDIA_CASE(TYPE) case MediaType::TYPE: mptr = TYPE::usercreated(); break;
		switch (mt) {
		MEDIA_CASE(Videogame);
		MEDIA_CASE(Movie);
		MEDIA_CASE(Music);
		default:	
			printf("Couldn't determine \"%s\" as a media type!\n", ps.cb.GetToken(1));
			return;
		}
		// printf("Got pointer: %p\n", mptr);
		ps.medias.push_back(mptr);
	}

	void Toggle(ProgState& ps) {
		if (ps.cb.Tokens() < 2) {
			printf("Expected a column argument: \" toggle [column]\"\n");
			return;
		}
		const Media::Var mv = Media::getVar(ps.cb.GetLowerToken(1));
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
		printf("%s: %i, didn't find what should've been a match!\n", __FILE__, __LINE__);
	} 

	void EnableCols(ProgState& ps) {
		for (size_t i=0;i<TableState::COL_CT;i++) ps.ts.COL_ENABLED[i] = true;
		printf("All columns visible!\n");
	}

	// Restore media vector to a copy of instances in the original vector (uses copy constructor).
	void Default(ProgState& ps) {
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
	}
	
	void Buckets(ProgState& ps) {
		printf("Max Size: %u, Max Buckets: %u, Max Load Factor: %f\n", 
			cmd_map.max_size(),cmd_map.max_bucket_count(),cmd_map.max_load_factor());	
		const size_t buckets = cmd_map.bucket_count();
		printf("Size: %u, Buckets: %u, Load Factor: %f\n", cmd_map.size(),buckets,cmd_map.load_factor());
		for (size_t i=0;i<buckets;i++) {
			printf("Bucket %u:", i);
			for (auto bckt_it = cmd_map.cbegin(i);bckt_it!=cmd_map.cend(i);++bckt_it) {
				printf(" %s", bckt_it->first.ptr);
			}
			printf("\n");
		}
	}

	void Help(ProgState& ps) {
		const char* const prefix = "	";
		printf("Help:\n");
		size_t maxlen = 0; // strlen(cmd) + 1 + strlen(args)
		for (auto it = cmd_map.cbegin();it!=cmd_map.cend();++it) {
			size_t len = strlen(it->first.ptr) + 1 + strlen(it->second.args);
			if (len > maxlen) maxlen = len;
		}

		const size_t CMAXLEN = maxlen;
		char cmddef[CMAXLEN+1]; // allow for null terminating char
		for (auto it = cmd_map.cbegin();it!=cmd_map.cend();++it) {	
			snprintf(cmddef, CMAXLEN+1, strlen(it->second.args)<1 ? "%s":"%s %s", it->first.ptr, it->second.args);
			printf("%*s - %s\n", CMAXLEN, cmddef, it->second.help);
		}
	}
};

int main() {
	// Instantiate default TableState, program is running, default CommandBuf, default originals, and blank currents.
	ProgState ps = { // Since all command functions receive same arguments, this is the single common arg.
		TableState(), true, CommandBuf(), makeDefaultMedias(), {}
	};

	while (ps.running) { // Keep prompting for commands as long as user hasn't ended program/
		ps.cb("> "); // Prompt user for input
		if (ps.cb.Tokens() < 1) continue; // If no tokens are passed, skip loop.
		const char* cmd = ps.cb.GetLowerToken(0); // Commands are case-INSENSITIVE.
		try { // Try to find the user's command!
			CommandDefinition::Function func = Command::cmd_map.at({cmd}).func; // Find command function from key.
			func(ps); // Call found function using the current ProgState 
		} catch (...) { printf("\"%s\" is not a known command!\n", ps.cb.GetToken(0)); } // When key is not found in map.
	}	

	return 0;
}
