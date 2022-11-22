#pragma once
#include "media.h"

// Music is a type of media with artist, publisher, and duration variables.
class Music : public Media {
private:
	// Variables specific to Music, not implemented in Media base.
	char *artist, *publisher;
	Duration duration;
	
	// Default constructor
	Music();

public:

	// Construct from values
	Music(const_cstr& title, const uint& year,
		const_cstr& artist, const_cstr& publisher, const Duration& duration);
	
	Music(const Music& o); // Copy constructor
	~Music() override; // Virtual destructor

	static Music* usercreated(); // Create music instance from console inputted values.

	// Return pointers to Music variables.
	const Duration* getDuration() const override;
	const char* getCreator() const override;
	const char* getPublisher() const override;

	// Return true if any matches to cstring are found (even with float and integer vars).
	bool search(const char*) const override;
};
