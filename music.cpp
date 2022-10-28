#include "music.h"

Music::Music(const_cstr& title, const uint& year,
	const_cstr& artist, const_cstr& publisher, const Duration& duration)
	: Media(title,year), duration(duration)
{	
	ALLOCCPY(artist);
	ALLOCCPY(publisher);
}
Music::~Music() {
	delete[] this->artist;
	delete[] this->publisher;
}
void Music::print() const {
	this->Media::print();
	printf("%*s %*s %*u:%0*u:%0*u ", 
		COL_WIDTH[0], artist,
		COL_WIDTH[1], publisher,
		3, duration.hours, // 3 + 2 + 2 + (2 semicolons) = 9 chars
		2, duration.mins, 
		2, duration.secs);
	
}
void Music::printHeader() {
	Media::printHeader();
	printf("%*s %*s %*s ",
		COL_WIDTH[0], "Artist",
		COL_WIDTH[1], "Publisher",
		COL_WIDTH[2], "Duration");	
}

const Duration* Music::getDuration() const { return &duration; }
const char* Music::getCreator() const { return artist; }
const char* Music::getPublisher() const { return publisher; }