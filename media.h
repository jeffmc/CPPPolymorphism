#pragma once
#include "types.h"

enum class MediaType {
	UnknownType, Videogame, Movie, Music
};

class Media { // TITLE / YEAR
	private:
		char* title; // pointer to title of this media. (Owned by this class)
		uint year; // year in which media was released
		constexpr static int COL_WIDTH[2] = { 15, 5 };
	
	public:
		static const int COL_SPACING = 2;
		Media(const_cstr& title, const uint& year);
		virtual ~Media();
		void print(); 
		static void printHeader();
};
