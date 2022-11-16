#pragma once

#include <vector>

// This class is meant to handle user input from stdin.
// It tokenizes whatever input is recieved and makes it accessible to user.
// Everything stays in its original case.
class CommandBuf {
private:
	const char* m_Raw;
	const char* m_LowerRaw;
	const char* m_Tokenized;
	const char* m_LowerTokenized;
	std::vector<const char*> m_Tokens;
public:
	const char* GetRaw() const; // Return unseperated string
	const char* GetLowerRaw() const; // Return unseperated string
	const char* GetToken(size_t i) const; // return token
	const char* GetLowerToken(size_t i) const; // return token
	const size_t Tokens() const; // return number of tokens	
	
	void operator()(const char* prefix); // Get command from buffer using specified prefix
	
	// Debug functions
	void printtkns() const;
};
