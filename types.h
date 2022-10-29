#pragma once
// Type definitons for classes assignment

#include <cstring>
#include <iostream>

// Day:Hour:Min:Sec
typedef unsigned char uchar;
struct Duration {	
	uchar hours;
	uchar mins;
	uchar secs; // 0-23, 0-59, 0-59
	Duration(uchar hours, uchar mins, uchar secs)
		: hours(hours), mins(mins), secs(secs) { };
	static int cmp(const Duration &a, const Duration &b);
};
struct Date {
	unsigned long year; //0-infinity (sorry BC)
	unsigned char days, month; // 1-31, 1-11
};
typedef const char*const const_cstr;
typedef unsigned int uint;
#define ALLOCCPY(arg) this->arg = new char[strlen(arg)+1]; strcpy(this->arg, arg);
