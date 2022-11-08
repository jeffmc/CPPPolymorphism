#include "movie.h"

Movie::Movie(const_cstr& title, const uint& year,
	const_cstr& director, const Duration& duration, const float& rating) 
	: Media(title, year), duration(duration), rating(rating)
{
	ALLOCCPY(director);
}
Movie::Movie(const Movie& o) : Media(o), duration(o.duration), rating(o.rating) {
	director = new char[strlen(o.director)+1];
	strcpy(director, o.director);
}
Movie::~Movie() {
	delete[] director;
}

const float* Movie::getRating() const { return &rating; }
const Duration* Movie::getDuration() const { return &duration; }
const char* Movie::getCreator() const { return director; }

bool Movie::search(const char* key) const {
	return Media::search(key) 
		|| strstr(director, key)
		|| strtof(key, nullptr) == rating;
} 
Movie* Movie::usercreated() {
	return nullptr;
}
