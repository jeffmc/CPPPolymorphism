#include "media.h"

class Music : public Media {
	private:
		char* artist, *publisher;
		Duration duration;
	public:
		Music(const_cstr& title, const uint& year,
			const_cstr& artist, const Duration& duration, const_cstr& publisher);
		~Music();
};
