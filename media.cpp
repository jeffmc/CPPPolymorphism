#include <cstring>
#include "media.h"

Media::Media(const_cstr& title, const uint& year) {
	ALLOCCPY(title);
	this->year = year;
}
Media::~Media() {
	delete[] this->title;
}
void Media::print() const {
	printf("%*s %*i ", 
		COL_WIDTH[0], this->title,
		COL_WIDTH[1], this->year);
}
void Media::printHeader() {
	printf("%*s %*s ", 
		COL_WIDTH[0], "Title",
		COL_WIDTH[1], "Year");
}

int Media::cmp(const Media::Var v, const Media* a, const Media* b) {
	switch (v) {
	case Title:
		return strcmp(a->title, b->title);
	case Year:
		return a->year - b->year;
	case Rating:
		const float *ar = a->getRating(), *br = b->getRating();
		if (ar && br) {
			const float diff = *ar - *br;
			if (diff == 0) return 0;
			return diff < 0 ? -1 : 1;
		} else {
			if (ar==nullptr&&br==nullptr) return 0;
			return (ar==nullptr)?1:-1;
		}
		break;
	case Duration:
		const Duration *ad = a->getDuration(), *bd = b->getDuration();
		if (ar && br) {
			return Duration::cmp(*ad, *bd);
		} else {
			if (ad==nullptr&&bd==nullptr) return 0;
			return (ad==nullptr)?1:-1;
		}
		break;
	case Creator:
		const char *as = a->getCreator(), *bs = b->getCreator();
		if (as && bs) {
			return strcmp(as,bs);
		} else {
			if (as==nullptr&&bs==nullptr) return 0;
			return (as==nullptr)?1:-1;
		}
		break;
	case Publisher:
		const char *as = a->getPublisher(), *bs = b->getPublisher();
		if (as && bs) {
			return strcmp(as,bs);
		} else {
			if (as==nullptr&&bs==nullptr) return 0;
			return (as==nullptr)?1:-1;
		}
		break;
	default: return 0;
	}
}

const char* Media::getTitle() const { return title; }
const uint* Media::getYear() const { return &year; }

const float* Media::getRating() const { return nullptr; }
const Duration* Media::getDuration() const { return nullptr; }
const char* Media::getCreator() const { return nullptr; }
const char* Media::getPublisher() const { return nullptr; }
