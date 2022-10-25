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
