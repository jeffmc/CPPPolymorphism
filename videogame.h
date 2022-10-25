#include "media.h"

class Videogame : public Media {
	private:
		char* publisher;
		float rating;
	public:
		Videogame(const_cstr& title, const uint& year,
				const_cstr publisher, const float& rating);
		~Videogame();
};