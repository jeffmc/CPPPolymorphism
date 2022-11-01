#pragma once
#include "media.h"

class Music : public Media {
private:
	char *artist, *publisher;
	Duration duration;

public:
	Music(const_cstr& title, const uint& year,
		const_cstr& artist, const_cstr& publisher, const Duration& duration);
	~Music();

	const Duration* getDuration() const override;
	const char* getCreator() const override;
	const char* getPublisher() const override;

	bool search(const char*) const override;
};
