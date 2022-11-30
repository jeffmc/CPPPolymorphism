#pragma once
#include <unordered_map>

#include "types.h"

// Enum used to determine which type of Media is which (typically using dynamic_cast, 
// and Run Time Type Identification, or RTTI for short).
enum class MediaType { // Enum classes are just better, if im not mistaken.
	UnknownType, Videogame, Movie, Music
};

// Media class, derived by Videogame, Music, and Movie classes.
// Has title cstring and year unsigned int.
// Often printed out to stdout in the main.cpp file.
class Media { // TITLE / YEAR
private:
	char* title; // pointer to title of this media. (Owned by this class)
	uint year; // year in which media was released

protected:
	Media(); // default initializer;

public:
	Media(const_cstr& title, const uint& year); // Construct from values (copies values)
	Media(const Media& o); // Copy constructor
	virtual ~Media(); // Virtual destructor, is good for polymorphic types!
	
	static const std::unordered_map<cstrkey, MediaType>& getStrTypeMap(); // Return a static const map of strings to MediaType enums
	static MediaType getType(const char* key); // Get a MediaType from a string

	enum class Var { Type, Title, Year, Rating, Duration, Creator, Publisher, NotFound }; // Enum of columns 
	static const std::unordered_map<cstrkey, Var>& getStrVarMap(); // Map of string to Media::Var 
	static Var getVar(const char* key); // Get Media::Var by string
	
	// Compare two medias "a" and "b" using variable "v".
	static int cmp(const Var v, const Media* a, const Media* b); 

	// Common media var setting	
	template <typename T>
	static T* usercreated(T* ptr) {
		static const size_t BUFSIZE = 256;
		char* input = new char[BUFSIZE]; // User-created medias will be incredibly inefficient in heap usage.

		printf("Title: ");
		CSTR_GETLINE(input,BUFSIZE);
		ptr->title = input;
		input = new char[BUFSIZE]; // last buffer now belongs to T instance

		printf("Year: ");
		CSTR_GETLINE(input,BUFSIZE);
		unsigned long t = strtoul(input,NULL,0);
		ptr->year = t;

		delete[] input; // Cleanup
		return ptr; // TODO: Return nullptr if input is invalid	
	}

	
	// These are not virtual functions because every media has title and year.
	const char* getTitle() const;
	const uint* getYear() const;

	// These are all virtual, may return nullptr if that media type doesn't have the desired variable.
	virtual const float* getRating() const;
	virtual const Duration* getDuration() const;
	virtual const char* getCreator() const;
	virtual const char* getPublisher() const;
	
	// Returns true if the cstring was contained within any of the media types cstrings,
	// or if when converted to int and float types, any numerical matches are found.
	virtual bool search(const char*) const;
};
