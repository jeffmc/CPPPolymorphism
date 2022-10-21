// Type definitons for classes assignment

#include <cstring>
#include <iostream>

// Day:Hour:Min:Sec
typedef unsigned char uchar;
struct Duration {
	
	unsigned long days; // 0-infinity
	uchar hours;
	uchar mins;
	uchar secs; // 0-23, 0-59, 0-59
	Duration(unsigned long days, uchar hours, uchar mins, uchar secs)
		: days(days), hours(hours), mins(mins), secs(secs) { };
};
struct Date {
	unsigned long year; //0-infinity (sorry BC)
	unsigned char days, month; // 1-31, 1-11
};
typedef const char*const const_cstr;
typedef unsigned int uint;
#define ALLOCCPY(arg) this->arg = new char[strlen(arg)+1]; strcpy(this->arg, arg); 
class Media {
	private:
		char* title; // pointer to title of this media. (Owned by this class)
		uint year; // year in which media was released
	public:
		Media(const_cstr& title, const uint& year) {
			ALLOCCPY(title);
			this->year = year;
		}
		~Media() {
			delete[] this->title;
		}
};
class Videogame : private Media {
	private:
		char* publisher;
		float rating;
	public:
		Videogame(const_cstr& title, const uint& year,
				const_cstr publisher, const float& rating) 
			: Media(title, year)
		{
			ALLOCCPY(publisher);
			this->rating = rating;
		}
		~Videogame() {
			delete[] this->publisher;
		}
};
class Music : private Media {
	private:
		char* artist, *publisher;
		Duration duration;
	public:
		Music(const_cstr& title, const uint& year,
				const_cstr& artist, const_cstr& publisher)
			: Media(title,year)
		{	
			ALLOCCPY(artist);
			ALLOCCPY(publisher);
		}
		~Music() {
			delete[] this->artist;
			delete[] this->publisher;
		}
};
class Movie : private Media {
	private:
		char* director;
		Duration duration;
		float rating;
	public:
		Movie(const_cstr& title, const uint& year,
				const_cstr& director, const Duration& duration, const float& rating)
			: Media(title, year)
		{
			ALLOCCPY(director);
			this->duration = duration;
			this->rating = rating;
		}
		~Movie() {
			delete[] director;
		}
};
