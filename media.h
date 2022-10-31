#pragma once
#include "types.h"

enum class MediaType {
	UnknownType, Videogame, Movie, Music
};

class Media { // TITLE / YEAR
	private:
		char* title; // pointer to title of this media. (Owned by this class)
		uint year; // year in which media was released

	public:
		Media(const_cstr& title, const uint& year);
		virtual ~Media();
		
		enum class Var { Type, Title, Year, Rating, Duration, Creator, Publisher, NotFound };
		static int cmp(const Var v, const Media* a, const Media* b);

		const char* getTitle() const;
		const uint* getYear() const;

		virtual const float* getRating() const;
		virtual const Duration* getDuration() const;
		virtual const char* getCreator() const;
		virtual const char* getPublisher() const;
};
