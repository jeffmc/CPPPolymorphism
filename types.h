// Type definitons for classes assignment

#include <cstring>
#include <iostream>
#include <cstdio>

// Day:Hour:Min:Sec
typedef unsigned char uchar;
struct Duration {	
	uchar hours;
	uchar mins;
	uchar secs; // 0-23, 0-59, 0-59
};
struct Date {
	unsigned long year; //0-infinity (sorry BC)
	unsigned char days, month; // 1-31, 1-11
};
typedef const char*const const_cstr;
typedef unsigned int uint;
#define ALLOCCPY(arg) this->arg = new char[strlen(arg)+1]; strcpy(this->arg, arg); 
class Media {
	protected:
		char* title; // pointer to title of this media. (Owned by this class)
		uint year; // year in which media was released
	public:
		virtual void print() const =0;
		Media(const_cstr& title, const uint& year) {
			ALLOCCPY(title);
			this->year = year;
		}
		~Media() {
			delete[] this->title;
		}
};
class Videogame : public Media {
	private:
		char* publisher;
		float rating;
	public:
		void print() const override {
			printf("%15s %4d %15s %-20.2f\n",
					this->title,this->year,this->publisher,this->rating);
		}
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
class Music : public Media {
	private:
		char* artist, *publisher;
		Duration duration;
	public:
		void print() const override {
			printf("%15s %4d %15s %-20s %2d:%2d:%2d\n",
					this->title,this->year,this->artist,
					this->publisher,
					this->duration.hours,this->duration.mins,this->duration.secs);
		}
		Music(const_cstr& title, const uint& year,
				const_cstr& artist, const Duration& duration, const_cstr& publisher)
			: Media(title,year)
		{	
			ALLOCCPY(artist);
			ALLOCCPY(publisher);
			this->duration = duration;
		}
		~Music() {
			delete[] this->artist;
			delete[] this->publisher;
		}
};
class Movie : public Media {
	private:
		char* director;
		Duration duration;
		float rating;
	public:
		void print() const override {
			printf("%15s %4d %15s %-20.2f %2d:%2d:%2d\n",
					this->title,this->year,this->director,
					this->rating,
					this->duration.hours,this->duration.mins,this->duration.secs);
		}
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
