#pragma once
#include "media.h"

// Movie is a type of media, with director, duration, and rating variables.
class Movie : public Media {
private:
	// Variable specific to Movie, not implemented in Media
	char* director;
	Duration duration;
	float rating;

	Movie();

public:
	// Construct from values
	Movie(const_cstr& title, const uint& year,
			const_cstr& director, const Duration& duration, const float& rating);
	
	Movie(const Movie& o); // Copy constructor
	~Movie() override; // Virtual destructor
	
	static Movie* usercreated(); // Create a new instance from user input on command line.
	
	// Return pointers to variable.
	const float* getRating() const override; 
	const Duration* getDuration() const override;
	const char* getCreator() const override;
	
	// Return true if any matches found from key
	bool search(const char*) const override;
};
