#pragma once
#include "media.h"

class Videogame : public Media {
private:
	char* publisher;
	float rating;
public:
	Videogame(const_cstr& title, const uint& year,
			const_cstr publisher, const float& rating);
	Videogame(const Videogame& vg);
	~Videogame();

	static Videogame* usercreated();

	const float* getRating() const override;
	const char* getPublisher() const override;
	
	bool search(const char*) const override;
};
