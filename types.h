#pragma once
// Type definitons for classes assignment
#include <cstring>
#include <iostream>
#include <limits>

#define CSTR_GETLINE(ptr, bufsize) std::cin.get(ptr, bufsize); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

// Day:Hour:Min:Sec
typedef unsigned char uchar;
struct Duration {	// Custom type for media variables.
	uchar hours;
	uchar mins;
	uchar secs; // 0-23, 0-59, 0-59
	Duration() { };
	Duration(uchar hours, uchar mins, uchar secs)
		: hours(hours), mins(mins), secs(secs) { };
	static int cmp(const Duration &a, const Duration &b); // Defined in main.cpp
	static Duration usercreated(const char* indent) {
		constexpr size_t BUFSIZE = 16;
		char* input = new char[BUFSIZE]; // small size due to small data-types
		Duration d;
		printf("%sHours: ", indent);
		CSTR_GETLINE(input, BUFSIZE);
		d.hours = strtoul(input,NULL,0);
		printf("%sMinutes: ", indent);
		CSTR_GETLINE(input, BUFSIZE);
		d.mins = strtoul(input,NULL,0);
		printf("%sSeconds: ", indent);
		CSTR_GETLINE(input, BUFSIZE);
		d.secs = strtoul(input,NULL,0);
		delete[] input;
		return d;
	};
};

// Used as key in std::unordered_map
struct cstrkey {
	const char* const ptr; 
	
	bool operator==(const cstrkey& o) const { 
		return strcmp(ptr, o.ptr) == 0;
	}
};

// Borrowed from https://stackoverflow.com/a/7666577
template<>
struct std::hash<cstrkey> {
	std::size_t operator()(const cstrkey& val) const { 
		const char* str = val.ptr; 
		unsigned long hash = 5381;
		int c;
		while (c = *str++)
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

		return hash;
	}
};

typedef const char*const const_cstr; // Const pointer to const cstring
typedef unsigned int uint; // unsigned int 

// Macro to heap alloc a cstr of strlen(arg)+1, for this->arg to be copied into.
#define ALLOCCPY(arg) this->arg = new char[strlen(arg)+1]; strcpy(this->arg, arg);
