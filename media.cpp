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
