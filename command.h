#pragma once

#include <vector>
#include <string> // TODO: No more of this!

// This class is meant to handle user input from stdin.
// It tokenizes whatever input is recieved and makes it accessible to user.
// Everything stays in its original case.
class CommandBuf {
private:
	std::string m_Raw;
	std::vector<std::string> m_Tokens;
public:
	const char* GetRaw() const; // Return unseperated string
	const char* GetToken(size_t i) const; // return token
	const size_t Tokens() const; // return number of tokens	
	
	std::string GetLine() const; // Get independent line of input from user, has no effect on raw or tokens.
	void operator()(const char* prefix); // Get command from buffer using specified prefix
	
	// Debug functions
	//void printdbg() const;
	void printtkns() const;
};
