#include <vector>
#include <string>

class CommandBuf {
private:
	std::string m_Raw;
	std::vector<std::string> m_Tokens;
public:
	const char* GetRaw() const; // Return unseperated string
	const char* GetToken(size_t i) const; // return token
	const size_t Tokens() const; // return number of tokens	
	
	void operator()(const char* prefix); // Get command from buffer using specified prefix
	
	//void printdbg() const;
	void printtkns() const;
};
