#include "media.h"

Media::Media(const_cstr& title, const uint& year) {
	ALLOCCPY(title);
	this->year = year;
}
Media::~Media() {
	delete[] this->title;
}
void Media::print() {
	printf("%*s%*c%*i%*c", 
		COL_WIDTH[0], this->title, COL_SPACING, ' ',
		COL_WIDTH[1], this->year, COL_SPACING, ' ');
}
void Media::printHeader() {
	printf("%*s%*c%*s%*c", 
		COL_WIDTH[0], "Title", COL_SPACING, ' ',
		COL_WIDTH[1], "Year", COL_SPACING, ' ');
}
