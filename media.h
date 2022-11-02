#pragma once
#include <unordered_map>
#include <string>

#include "types.h"

enum class MediaType {
	UnknownType, Videogame, Movie, Music
};

class Media { // TITLE / YEAR
private:
	char* title; // pointer to title of this media. (Owned by this class)
	uint year; // year in which media was released

public:
	Media(const_cstr& title, const uint& year);
	virtual ~Media();
	
	static const std::unordered_map<std::string, MediaType>& getStrTypeMap();
	static MediaType getType(const std::string& key);

	enum class Var { Type, Title, Year, Rating, Duration, Creator, Publisher, NotFound };
	static const std::unordered_map<std::string, Var>& getStrVarMap();
	static Var getVar(const std::string& key);
	
	static int cmp(const Var v, const Media* a, const Media* b);


	const char* getTitle() const;
	const uint* getYear() const;

	virtual const float* getRating() const;
	virtual const Duration* getDuration() const;
	virtual const char* getCreator() const;
	virtual const char* getPublisher() const;
	
	virtual bool search(const char*) const;
};
