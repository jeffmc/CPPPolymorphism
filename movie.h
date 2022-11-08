#pragma once
#include "media.h"

class Movie : public Media {
private:
	char* director;
	Duration duration;
	float rating;
public:
	Movie(const_cstr& title, const uint& year,
			const_cstr& director, const Duration& duration, const float& rating);
	Movie(const Movie& o);
	~Movie();
	
	static Movie* usercreated();
	
	const float* getRating() const override;
	const Duration* getDuration() const override;
	const char* getCreator() const override;
	
	bool search(const char*) const override;
};
