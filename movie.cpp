#include "movie.h"

Movie::Movie() : Media(), director(nullptr) {}

// Construct from values
Movie::Movie(const_cstr& title, const uint& year,
	const_cstr& director, const Duration& duration, const float& rating) 
	: Media(title, year), duration(duration), rating(rating)
{
	ALLOCCPY(director);
}

// Copy constructor
Movie::Movie(const Movie& o) : Media(o), duration(o.duration), rating(o.rating) {
	director = new char[strlen(o.director)+1];
	strcpy(director, o.director);
}

// Destructor
Movie::~Movie() {
	delete[] director;
}

// Return pointers to variables
const float* Movie::getRating() const { return &rating; }
const Duration* Movie::getDuration() const { return &duration; }
const char* Movie::getCreator() const { return director; }

// Return true if any matches are found
bool Movie::search(const char* key) const {
	return Media::search(key) 
		|| strstr(director, key)
		|| strtof(key, nullptr) == rating;
} 

Movie* Movie::usercreated() {
	Movie* ptr = new Movie;
	if (!Media::usercreated(ptr)) return nullptr;
	static const size_t BUFSIZE = 256;
	char* input = new char[BUFSIZE]; // User-created medias will be incredibly inefficient in heap usage.

	printf("Director: ");
	CSTR_GETLINE(input, BUFSIZE);
	ptr->director = input;
	input = new char[BUFSIZE]; // last alloc now belongs to instance

	printf("Duration:\n");
	ptr->duration = Duration::usercreated("    ");

	printf("Rating: ");
	CSTR_GETLINE(input,BUFSIZE);
	ptr->rating = atof(input);
	
	delete[] input;
	return ptr;
}
