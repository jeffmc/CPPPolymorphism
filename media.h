#pragma once
#include "types.h"

enum class MediaType {
	UnknownType, Videogame, Movie, Music
};

class Media { // TITLE / YEAR
	private:
		char* title; // pointer to title of this media. (Owned by this class)
		uint year; // year in which media was released
		constexpr static int COL_WIDTH[2] = { 20, 4 };
	
	public:
		Media(const_cstr& title, const uint& year);
		virtual ~Media();
		virtual void print() const; 
		static void printHeader();
};
