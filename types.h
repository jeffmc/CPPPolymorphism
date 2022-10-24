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

#define ALLOCCPY(mem,arg) this->mem = new char[strlen(arg)+1]; strcpy(this->mem, arg); 

int memPrint(char* buf, const size_t& n, const float& mem) { return snprintf(buf,n,"%f", mem);	}
int memPrint(char* buf, const size_t& n, const char* mem) { return snprintf(buf,n,"%s", mem); }
int memPrint(char* buf, const size_t& n, const uint& mem) { return snprintf(buf,n,"%u", mem); }
int memPrint(char* buf, const size_t& n, const Duration& mem) { return snprintf(buf,n,"%u:%u:%u", mem.hours, mem.mins, mem.secs); }

#define VIRTMEMACC(NUM) virtual int printm##NUM(char* buf, const size_t& n) const =0;
#define V(n) VIRTMEMACC(n);
#define VIRTMEMACC2(n0,n1) 					 V(n0);V(n1);
#define VIRTMEMACC3(n0,n1,n2)				 V(n0);V(n1);V(n2);
#define VIRTMEMACC4(n0,n1,n2,n3) 			 V(n0);V(n1);V(n2);V(n3);
#define VIRTMEMACC5(n0,n1,n2,n3,n4) 		 V(n0);V(n1);V(n2);V(n3);V(n4);
#define VIRTMEMACC6(n0,n1,n2,n3,n4,n5) 		 V(n0);V(n1);V(n2);V(n3);V(n4);V(n5);
#define VIRTMEMACC7(n0,n1,n2,n3,n4,n5,n6) 	 V(n0);V(n1);V(n2);V(n3);V(n4);V(n5);V(n6);
#define VIRTMEMACC8(n0,n1,n2,n3,n4,n5,n6,n7) V(n0);V(n1);V(n2);V(n3);V(n4);V(n5);V(n6);V(n7);

#define MEMACC(NUM,MEM) int printm##NUM(char* buf, const size_t& n) const override { return memPrint(buf, n, this->MEM); }
#define MEMNULL(NUM)    int printm##NUM(char* buf, const size_t& n) const override { *buf = '\0'; return 0; }
#define MN(n) MEMNULL(n)
#define MEMNULL2(n0,n1) MN(n0);MN(n1);
#define MEMNULL3(n0,n1,n2) MN(n0);MN(n1);MN(n2);
#define MEMNULL4(n0,n1,n2,n3) MN(n0);MN(n1);MN(n2);MN(n3);
#define MEMNULL5(n0,n1,n2,n3,n4) MN(n0);MN(n1);MN(n2);MN(n3);MN(n4);
#define MEMNULL6(n0,n1,n2,n3,n4,n5) MN(n0);MN(n1);MN(n2);MN(n3);MN(n4);MN(n5);
#define MEMNULL7(n0,n1,n2,n3,n4,n5,n6) MN(n0);MN(n1);MN(n2);MN(n3);MN(n4);MN(n5);MN(n6);
#define MEMNULL8(n0,n1,n2,n3,n4,n5,n6,n7) MN(n0);MN(n1);MN(n2);MN(n3);MN(n4);MN(n5);MN(n6);MN(n7);

#define GENMEDACC() MEMACC(0,m_Title); MEMACC(1,m_Year);
class Media {
	protected:
		char* m_Title; // pointer to title of this media. (Owned by this class)
		uint m_Year; // year in which media was released
	public:
		virtual void print() const =0;

		VIRTMEMACC8(0,1,2,3,4,5,6,7);

		Media(const_cstr& title, const uint& year) {
			ALLOCCPY(m_Title,title);
			m_Year = year;
		}
		~Media() {
			delete[] m_Title;
		}
};

class Videogame : public Media {
	private:
		char* m_Publisher;
		float m_Rating;
	public:
		void print() const override {
			printf("%15s %4d %15s %-20.2f\n",
					m_Title,m_Year,m_Publisher,m_Rating);
		}

		GENMEDACC();
		MEMACC(2,m_Publisher);
		MEMACC(3,m_Rating);
		MEMNULL4(4,5,6,7);

		Videogame(const_cstr& title, const uint& year,
				const_cstr publisher, const float& rating) 
			: Media(title, year)
		{
			ALLOCCPY(m_Publisher,publisher);
			m_Rating = rating;
		}
		~Videogame() {
			delete[] m_Publisher;
		}
};
class Music : public Media {
private:
	char* m_Artist;
	char* m_Publisher;
	Duration m_Length;
public:
	void print() const override {
		printf("%15s %4d %15s %-20s %2d:%2d:%2d\n",
				m_Title,m_Year,m_Artist,m_Publisher,
				m_Length.hours,m_Length.mins,m_Length.secs);
	}

	GENMEDACC();
	MEMACC(2,m_Publisher);
	MEMACC(3,m_Artist);
	MEMACC(4,m_Length);
	MEMNULL3(5,6,7);	

	Music(const_cstr& title, const uint& year,
			const_cstr& artist, const Duration& length, const_cstr& publisher)
		: Media(title,year)
	{	
		ALLOCCPY(m_Artist,artist);
		ALLOCCPY(m_Publisher,publisher);
		m_Length = length;
	}
	~Music() {
		delete[] m_Artist;
		delete[] m_Publisher;
	}
};
class Movie : public Media {
private:
	char* m_Director;
	Duration m_Length;
	float m_Rating;
public:
	void print() const override {
		printf("%15s %4d %15s %-20.2f %2d:%2d:%2d\n",
				m_Title,m_Year,m_Director,m_Rating,
				m_Length.hours,m_Length.mins,m_Length.secs);
	}
	
	GENMEDACC();
	MEMACC(2,m_Director);
	MEMACC(3,m_Rating);
	MEMACC(4,m_Length);
	MEMNULL3(5,6,7);

	Movie(const_cstr& title, const uint& year,
			const_cstr& director, const Duration& length, const float& rating)
		: Media(title, year)
	{
		ALLOCCPY(m_Director,director);
		m_Length = length;
		m_Rating = rating;
	}
	~Movie() {
		delete[] m_Director;
	}
};

#undef V
#undef MN