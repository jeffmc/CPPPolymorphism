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
void Videogame::print() const {
	this->Media::print();
	printf("%*s %*g ", 
		COL_WIDTH[0], this->publisher,
		COL_WIDTH[1], this->rating);
	
}
void Videogame::printHeader() {
	Media::printHeader();
	printf("%*s %*s ",
		COL_WIDTH[0], "Publisher",
		COL_WIDTH[1], "Rating");	
}
