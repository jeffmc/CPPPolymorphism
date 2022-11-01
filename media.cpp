#include <cstring>
#include <string>
#include <unordered_map>

#include "media.h"

Media::Media(const_cstr& title, const uint& year) {
	ALLOCCPY(title);
	this->year = year;
}
Media::~Media() {
	delete[] this->title;
}

const std::unordered_map<std::string, Media::Var>& Media::getStrVarMap() {
	static std::unordered_map<std::string, Var> str_var_map = {
		{ "type", Media::Var::Type },
		{ "title", Media::Var::Title },
		{ "year", Media::Var::Year },
		{ "rating", Media::Var::Rating },
		{ "duration", Media::Var::Duration },
		{ "creator", Media::Var::Creator },
		{ "publisher", Media::Var::Publisher },
	};
	return str_var_map;
};

Media::Var Media::getVar(const std::string& key) {
	try {
		Media::Var found = Media::getStrVarMap().at(key);
		return found;
	} catch (...) { }
	return Media::Var::NotFound;		
}

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
			return (ar==nullptr)?1:-1;
		}
		break;
	case Var::Duration:
		ad = a->getDuration();
		bd = b->getDuration();
		if (ad && bd) {
			return Duration::cmp(*ad, *bd);
		} else {
			if (ad==nullptr&&bd==nullptr) return 0;
			return (ad==nullptr)?1:-1;
		}
		break;
	case Var::Creator:
		as = a->getCreator();
		bs = b->getCreator();
		if (as && bs) {
			return strcmp(as,bs);
		} else {
			if (as==nullptr&&bs==nullptr) return 0;
			return (as==nullptr)?1:-1;
		}
		break;
	case Var::Publisher:
		as = a->getPublisher();
		bs = b->getPublisher();
		if (as && bs) {
			return strcmp(as,bs);
		} else {
			if (as==nullptr&&bs==nullptr) return 0;
			return (as==nullptr)?1:-1;
		}
		break;
	}
	return 0;
}

const char* Media::getTitle() const { return title; }
const uint* Media::getYear() const { return &year; }

const float* Media::getRating() const { return nullptr; }
const Duration* Media::getDuration() const { return nullptr; }
const char* Media::getCreator() const { return nullptr; }
const char* Media::getPublisher() const { return nullptr; }

bool Media::search(const char* key) const {
	return strstr(title,key) || atoi(key) == year;	
};
