#include "videogame.h"

Videogame::Videogame(const_cstr& title, const uint& year,
	const_cstr publisher, const float& rating) : Media(title, year)
{
	ALLOCCPY(publisher);
	this->rating = rating;
}
Videogame::~Videogame() {
	delete[] this->publisher;
}
