#pragma once
#include "media.h"

class Music : public Media {
	private:
		char *artist, *publisher;
		Duration duration;
		constexpr static int COL_WIDTH[3] = { 20, 20, 9 };

	public:
		Music(const_cstr& title, const uint& year,
			const_cstr& artist, const_cstr& publisher, const Duration& duration);
		~Music();
		void print() const override;
		static void printHeader();

		const Duration* getDuration() const override;
		const char* getCreator() const override;
		const char* getPublisher() const override;
};
