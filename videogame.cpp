#include "videogame.h"

Videogame::Videogame() : Media(), publisher(nullptr) {}

Videogame::Videogame(const_cstr& title, const uint& year,
	const_cstr publisher, const float& rating)
	: Media(title, year), rating(rating)
{
	ALLOCCPY(publisher);
}
Videogame::Videogame(const Videogame& o) : Media(o), rating(o.rating) {
	publisher = new char[strlen(o.publisher)+1];
	strcpy(publisher,o.publisher);
}
Videogame::~Videogame() {
	delete[] this->publisher;
}

const float* Videogame::getRating() const { return &rating; }
const char* Videogame::getPublisher() const { return publisher; }

bool Videogame::search(const char* key) const {
	return Media::search(key) 
		|| strtof(key,nullptr) == rating 
		|| strstr(publisher,key);
} 
Videogame* Videogame::usercreated() {
	Videogame* ptr = new Videogame;
	if (!Media::usercreated(ptr)) return nullptr;

	static const size_t BUFSIZE = 256;
	char* input = new char[BUFSIZE]; // User-created medias will be incredibly inefficient in heap usage.
	
	printf("Rating: ");
	CSTR_GETLINE(input, BUFSIZE);
	ptr->rating = strtof(input, NULL);
	
	printf("Publisher: ");
	CSTR_GETLINE(input, BUFSIZE);
	ptr->publisher = input; // Don't delete or reassign unless inputting additional fields in future

	return ptr;
}
