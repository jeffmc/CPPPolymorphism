#include <cstring>
#include <unordered_map>

#include "media.h"

// Value constructor, copies arguments.
Media::Media(const_cstr& title, const uint& year) : year(year) {
	ALLOCCPY(title);
}
// Copy constructor (used for copying originals into the current medias.)
Media::Media(const Media& o) : year(o.year) {
	title = new char[strlen(o.title)+1];
	strcpy(title,o.title);
}
// Classic delete.
Media::~Media() {
	//printf("~Media() [%p]\n", this);
	delete[] this->title;
}

// Map lowercase strings to MediaType enum.
const std::unordered_map<cstrkey, MediaType>& Media::getStrTypeMap() {
	static const std::unordered_map<cstrkey, MediaType> str_type_map = {
		{ {"videogame"}, MediaType::Videogame },
		{     {"music"}, MediaType::Music },
		{     {"movie"}, MediaType::Movie },
	};
	return str_type_map;
};

// Get MediaType enum val from string.
MediaType Media::getType(const char* key) {
	try {
		MediaType found = Media::getStrTypeMap().at({key});
		return found;
	} catch (...) { }
	return MediaType::UnknownType;		
}

// Map strings to Media::Var
const std::unordered_map<cstrkey, Media::Var>& Media::getStrVarMap() {
	static std::unordered_map<cstrkey, Var> str_var_map = {
		{      {"type"}, Media::Var::Type },
		{     {"title"}, Media::Var::Title },
		{      {"year"}, Media::Var::Year },
		{    {"rating"}, Media::Var::Rating },
		{  {"duration"}, Media::Var::Duration },
		{   {"creator"}, Media::Var::Creator },
		{ {"publisher"}, Media::Var::Publisher },
	};
	return str_var_map;
};

// Get Media::Var enum val from string.
Media::Var Media::getVar(const char* key) {
	try {
		Media::Var found = Media::getStrVarMap().at({key});
		return found;
	} catch (...) { }
	return Media::Var::NotFound;		
}
// Compare two medias, "a" and "b" using the given variable "v"
int Media::cmp(const Media::Var v, const Media* a, const Media* b) {
	const char *as, *bs;
	const float *ar, *br;
	const Duration *ad, *bd; 
	switch (v) {
	case Var::Title:
		return strcmp(a->title, b->title);
	case Var::Year:
		return a->year - b->year;
	case Var::Rating:
		ar = a->getRating();
		br = b->getRating();
		if (ar && br) {
			const float diff = *ar - *br;
			if (diff == 0) return 0;
			return diff < 0 ? -1 : 1;
		} else {
			if (ar==nullptr&&br==nullptr) return 0;
			return (ar==nullptr)?-1:1;
		}
		break;
	case Var::Duration:
		ad = a->getDuration();
		bd = b->getDuration();
		if (ad && bd) {
			return Duration::cmp(*ad, *bd);
		} else {
			if (ad==nullptr&&bd==nullptr) return 0;
			return (ad==nullptr)?-1:1;
		}
		break;
	case Var::Creator:
		as = a->getCreator();
		bs = b->getCreator();
		if (as && bs) {
			return strcmp(as,bs);
		} else {
			if (as==nullptr&&bs==nullptr) return 0;
			return (as==nullptr)?-1:1;
		}
		break;
	case Var::Publisher:
		as = a->getPublisher();
		bs = b->getPublisher();
		if (as && bs) {
			return strcmp(as,bs);
		} else {
			if (as==nullptr&&bs==nullptr) return 0;
			return (as==nullptr)?-1:1;
		}
		break;
	default:
		printf("Unsortable Media::Var in Media::cmp()!\n");
		return 0;
	}
	return 0;
}

// Should always return valid pointers
const char* Media::getTitle() const { return title; }
const uint* Media::getYear() const { return &year; }

// May return nullptrs.
const float* Media::getRating() const { return nullptr; }
const Duration* Media::getDuration() const { return nullptr; }
const char* Media::getCreator() const { return nullptr; }
const char* Media::getPublisher() const { return nullptr; }

// Returns true if key is found within variables of media.
bool Media::search(const char* key) const {
	return strstr(title,key) || atoi(key) == year;	
};
