#pragma once
#include "media.h"

class Movie : public Media {
	private:
		char* director;
		Duration duration;
		float rating;
		constexpr static int COL_WIDTH[3] = { 20, 9, 6 };
	public:
		Movie(const_cstr& title, const uint& year,
				const_cstr& director, const Duration& duration, const float& rating);
		~Movie();
		void print() const override;
		static void printHeader();
		const float* getRating() const override;
		const Duration* getDuration() const override;
		const char* getCreator() const override;
};
