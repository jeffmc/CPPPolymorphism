#include "media.h"

Media::Media(const_cstr& title, const uint& year) {
	ALLOCCPY(title);
	this->year = year;
}
Media::~Media() {
	delete[] this->title;
}
