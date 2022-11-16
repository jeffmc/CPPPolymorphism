#include <iostream>
#include <vector>
#include <limits>

// Description of class found there.
#include "command.h"

// Getters
const char* CommandBuf::GetRaw() const { return m_Raw.c_str(); }
const char* CommandBuf::GetToken(size_t i) const { return m_Tokens[i].c_str(); }
const size_t CommandBuf::Tokens() const { return m_Tokens.size(); }	

static COMMANDBUFSIZE = 4096;
	 
void CommandBuf::operator()(const char* prefix) {	
	m_Raw = {};
	printf("%s", prefix);
	std::getline(std::cin, m_Raw);
	//printf("CommandBuf.cpp: Took input\n");
	
	m_Tokens.clear();
	const char* const whitespace = " \f\n\r\t\v";
	size_t x = m_Raw.find_first_not_of(whitespace,0);
	while (x < m_Raw.length()) {
		size_t y = m_Raw.find_first_of(whitespace,x);
		if (y == std::string::npos) { 
			m_Tokens.push_back(m_Raw.substr(x,y)); // len value of npos takes rest of string.
		} else {	
			m_Tokens.push_back(m_Raw.substr(x,y-x));
		}
		x = m_Raw.find_first_not_of(whitespace,y);
	}
}
/* // Comment out to hide compiler warnings, and its not really used.
void CommandBuf::printdbg() const {
	static const char* const INDENT = "	";

	void* self = (void*)this;
	size_t ssz = sizeof(decltype(*this));
	printf("CommandBuf(%u): %p-%p\n", ssz, self, self+ssz-1);
	
	void* rptr = (void*)&m_Raw;
	size_t rsz = sizeof(decltype(m_Raw));
	printf("%sRaw(%u): %p-%p\n",
		INDENT, sizeof(std::string), rptr, rptr+rsz-1);
	
	void* vptr = (void*)&m_Tokens;
	size_t vsz = sizeof(decltype(m_Tokens));
	printf("%sVector(%u): %p-%p\n",
		INDENT, vsz, vptr, vptr+vsz-1);
}
*/
void CommandBuf::printtkns() const {
	printf("Raw: \"%s\"\n", m_Raw.c_str());
	for (auto it = m_Tokens.cbegin(); it != m_Tokens.cend(); ++it) {
		printf("  \"%s\"\n", it->c_str());
	}
}

// Was intended for a feature that I decided against, also unnecessarily a non-static member.
std::string CommandBuf::GetLine() const {
	std::string line;
	std::getline(std::cin, line);
	return line;	
}
