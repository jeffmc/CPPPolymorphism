#include "media.h"

class Videogame : public Media {
	private:
		char* publisher;
		float rating;
		constexpr static int COL_WIDTH[2] = { 20, 6 };
	public:
		Videogame(const_cstr& title, const uint& year,
				const_cstr publisher, const float& rating);
		~Videogame();
		void print() const override;
		static void printHeader();
};
