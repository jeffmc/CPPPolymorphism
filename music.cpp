#include "music.h"

Music::Music(const_cstr& title, const uint& year,
	const_cstr& artist, const_cstr& publisher, const Duration& duration)
	: Media(title,year), duration(duration)
{	
	ALLOCCPY(artist);
	ALLOCCPY(publisher);
}
Music::Music(const Music& o) : Media(o), duration(o.duration) {
	artist = new char[strlen(o.artist)+1];
	strcpy(artist, o.artist);
	publisher = new char[strlen(o.publisher)+1];
	strcpy(publisher, o.publisher);
}
Music::~Music() {
	delete[] this->artist;
	delete[] this->publisher;
}

const Duration* Music::getDuration() const { return &duration; }
const char* Music::getCreator() const { return artist; }
const char* Music::getPublisher() const { return publisher; }

bool Music::search(const char* key) const {
	return Media::search(key) 
		|| strstr(artist,key)
		|| strstr(publisher,key);
} 

Music* Music::usercreated() {
	return nullptr;
}
