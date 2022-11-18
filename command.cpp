#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <cctype>

// Description of class found there.
#include "command.h"

// Getters
const char* CommandBuf::GetRaw() const { return m_Raw; }
const char* CommandBuf::GetLowerRaw() const { return m_LowerRaw; }

const char* CommandBuf::GetToken(size_t i) const { return m_Tokens[i]; }
const char* CommandBuf::GetLowerToken(size_t i) const {
	std::ptrdiff_t offset = m_Tokens[i] - m_Tokenized; 
	return m_LowerTokenized + offset;
}

const size_t CommandBuf::Tokens() const { return m_Tokens.size(); }	
static size_t CMDBUFSIZE = 4096; // Static global is only defined for this file.
	 
void CommandBuf::operator()(const char* prefix) {	
	if (m_Raw) delete[] m_Raw;
	if (m_LowerRaw) delete[] m_LowerRaw;
	if (m_Tokenized) delete[] m_Tokenized;
	if (m_LowerTokenized) delete[] m_LowerTokenized;
	
	// Take raw input (TODO: Filter characters using isprint() )
	char* raw = new char[CMDBUFSIZE];
	printf("%s", prefix);
	std::cin.get(raw, CMDBUFSIZE);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	m_Raw = raw;

	// Make tokenized
	m_Tokens.clear();
	char* moving = new char[CMDBUFSIZE];	
	memcpy(moving, m_Raw, CMDBUFSIZE);	
	m_Tokenized = moving;	
	while (*moving) { // Run non-null
		if (isspace(*moving)) { // Ignore spaces
			++moving;
		} else { // If non-whitespace
			m_Tokens.push_back(moving); // Add the start to vec
			while ( ( !isspace(*moving) ) && (*moving) ) ++moving; // Move till whitespace/end.
			if (*moving) { // If not already at end
				*moving = '\0'; // Mark end of token with null char
				++moving; // Move to next char to keep while loop running.
			}
		}
	}

	// Make lower variants.
	char* lr = new char[CMDBUFSIZE];
	memcpy(lr,m_Raw,CMDBUFSIZE);
	m_LowerRaw = lr;
	char* lt = new char[CMDBUFSIZE];
	memcpy(lt,m_Tokenized,CMDBUFSIZE);
	m_LowerTokenized = lt;
	while (*lr) {
		*(lr++) = tolower(*lr);
		*(lt++) = tolower(*lt);
	}
}

void CommandBuf::printtkns() const {
	printf("Raw: \"%s\"\n", m_Raw);
	for (auto it = m_Tokens.cbegin(); it != m_Tokens.cend(); ++it) {
		printf("  \"%s\"\n", (*it));
	}
	printf("LowerRaw: \"%s\"\n", m_LowerRaw);
	for (size_t i = 0; i < this->Tokens(); ++i) {
		printf("  \"%s\"\n", this->GetLowerToken(i));
	}
}
