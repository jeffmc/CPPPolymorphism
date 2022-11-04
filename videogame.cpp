#include "videogame.h"

Videogame::Videogame(const_cstr& title, const uint& year,
	const_cstr publisher, const float& rating)
	: Media(title, year), rating(rating)
{
	ALLOCCPY(publisher);
}
Videogame::~Videogame() {
	delete[] this->publisher;
}

const float* Videogame::getRating() const { return &rating; }
const char* Videogame::getPublisher() const { return publisher; }

bool Videogame::search(const char* key) const {
	return Media::search(key) 
		|| strtof(key,nullptr) == rating 
		|| strstr(publisher,key);
} 
Videogame* Videogame::usercreated() {
	return nullptr;
}
