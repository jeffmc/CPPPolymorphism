#pragma once
#include "media.h"

// Videogame is a type of media, with publisher and rating variables.
class Videogame : public Media {
private:
	// Videogame specific variables, not contained in base class Media.
	char* publisher;
	float rating;
public:
	// Construct from values
	Videogame(const_cstr& title, const uint& year,
			const_cstr publisher, const float& rating);
	
	Videogame(const Videogame& vg); // Copy constructor
	~Videogame() override; // Virtual destructor

	static Videogame* usercreated(); // Create videogame instance from user inputted values.

	// Return Videogame variable pointers.
	const float* getRating() const override;
	const char* getPublisher() const override;
	
	// Return true if any matches are found.
	bool search(const char*) const override;
};
