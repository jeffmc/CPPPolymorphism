#include "music.h"

Music::Music() : Media(), artist(nullptr), publisher(nullptr) {}

Music::Music(const_cstr& title, const uint& year,
	const_cstr& artist, const_cstr& publisher, const Duration& duration)
	: Media(title,year), duration(duration)
{	
	ALLOCCPY(artist);
	ALLOCCPY(publisher);
}
Music::Music(const Music& o) : Media(o), duration(o.duration) {
	artist = new char[strlen(o.artist)+1];
	strcpy(artist, o.artist);
	publisher = new char[strlen(o.publisher)+1];
	strcpy(publisher, o.publisher);
}
Music::~Music() {
	delete[] this->artist;
	delete[] this->publisher;
}

const Duration* Music::getDuration() const { return &duration; }
const char* Music::getCreator() const { return artist; }
const char* Music::getPublisher() const { return publisher; }

bool Music::search(const char* key) const {
	return Media::search(key) 
		|| strstr(artist,key)
		|| strstr(publisher,key);
} 

Music* Music::usercreated() {
	Music* ptr = new Music;
	if (!Media::usercreated(ptr)) return nullptr;
	static const size_t BUFSIZE = 256;
	char* input = new char[BUFSIZE]; // User-created medias will be incredibly inefficient in heap usage.

	printf("Artist: ");
	CSTR_GETLINE(input, BUFSIZE);
	ptr->artist = input;
	input = new char[BUFSIZE]; // last alloc now belongs to instance

	printf("Duration:\n");
	ptr->duration = Duration::usercreated("    ");
	
	printf("Publisher: ");
	CSTR_GETLINE(input, BUFSIZE);
	ptr->publisher = input; // Don't delete or reassign unless inputting additional fields in future

	return ptr;
}
