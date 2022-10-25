#include "music.h"

Music::Music(const_cstr& title, const uint& year,
	const_cstr& artist, const Duration& duration, const_cstr& publisher)
	: Media(title,year), duration(duration)
{	
	ALLOCCPY(artist);
	ALLOCCPY(publisher);
}
Music::~Music() {
	delete[] this->artist;
	delete[] this->publisher;
}
