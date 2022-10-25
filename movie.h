#include "media.h"

class Movie : public Media {
	private:
		char* director;
		Duration duration;
		float rating;
	public:
		Movie(const_cstr& title, const uint& year,
				const_cstr& director, const Duration& duration, const float& rating);
		~Movie();
};
