#pragma once
#include "types.h"

class Media {
	private:
		char* title; // pointer to title of this media. (Owned by this class)
		uint year; // year in which media was released
	public:
		Media(const_cstr& title, const uint& year);
		virtual ~Media();
};
