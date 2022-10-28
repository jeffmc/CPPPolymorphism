#include "movie.h"

Movie::Movie(const_cstr& title, const uint& year,
	const_cstr& director, const Duration& duration, const float& rating) 
	: Media(title, year), duration(duration), rating(rating)
{
	ALLOCCPY(director);
}
Movie::~Movie() {
	delete[] director;
}
void Movie::print() const {
	this->Media::print();
	printf("%*s %*u:%0*u:%0*u %*f ",
		COL_WIDTH[0],director,
		3,duration.hours,
		2,duration.mins,
		2,duration.secs,
		COL_WIDTH[2], rating);
}
void Movie::printHeader() {
	Media::printHeader();
	printf("%*s %*s %*s ",
		COL_WIDTH[0], "Director",
		COL_WIDTH[1], "Duration",
		COL_WIDTH[2], "Rating");	
}
