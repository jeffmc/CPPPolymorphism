#pragma once

#include <vector>

#include "types.h"
#include "media.h"
#include "command.h"

// This file contains some global function declarations and some structs, all necessary for this program.

int main(); // Entry point

MediaType getMediaTypeFromPtr(Media* m); // Return MediaType enum val for given Media pointer.
const char* getMediaTypeStr(const MediaType &mt); // Return a cstring label for given MediaType.

// Store the width of columns, whether columns are visible,
// Static members also determine left-align, number of columns, column titles, and enums.
struct TableState {
public:
	static constexpr int COL_CT = 7; // TODO: COMPILATION ERROR: UNDEFINED REF TO THESE IN printHeader() ???
	static constexpr bool COL_LA[COL_CT]     = {false, false, false, true, false, false, true };
	// TODO: Unify this definition and the names within map in Media::getStrVarMap();
	static constexpr const char* COL_NAMES[COL_CT] = {"Type", "Title", "Year", "Creator", "Rating", "Duration", "Publisher" };
	static constexpr Media::Var COL_VARS[COL_CT] = { Media::Var::Type, Media::Var::Title, Media::Var::Year,
		 Media::Var::Creator, Media::Var::Rating, Media::Var::Duration, Media::Var::Publisher };
	
	// Non-static non-const members
	int COL_WIDTH[COL_CT] = { 15, 25, 4, 25, 6, 9, 25 }; // TODO: Allow user to modify widths (EXCEPT DURATION)
	bool COL_ENABLED[COL_CT] = { false, true, true, true, true, true, true }; // modifiable through toggle cmd
};

// print out the column titles filling each column width.
void printHeader(const TableState& ts);

// Swap two elements at given indices within a vector.
template<typename T>
void vecswap(std::vector<T> &v, const size_t a, const size_t b);

// print a table of medias (doesn't print the header)
void printMedias(const TableState& ts, const std::vector<Media*> &medias);

// ProgState is passed to each of the command functions, it contains the media vector, 
// the original media vector, the tablestate, and the running boolean (affected by quit command).
struct ProgState {
	TableState ts; // Contains info about formatting the printed table of medias.
	bool running; // If set to false within command, user will NOT be prompted for additional command and program will end.
	CommandBuf cb; // Contains user-input
	const std::vector<Media*> originals; // Seperate instances from the media, these pointers should never be deleted.
	std::vector<Media*> medias; // Could contain additional user-defined media, or none at all. 
};

// Store command keywords, arguments, and descriptions.
struct CommandDefinition {
	using Function = void(*)(ProgState&); // Called when key is found in 0th arg of CommandBuf
	const Function func;
	const char* const args;
	const char* const help;	
};

// Commands TODO: Put in their own namespace!
namespace Command {
	void Sort(ProgState& ps);       // Sort the media by a given column variable, look at Media::cmp(...)
	void Size(ProgState& ps);       // Print out the size of media vectors (defaults and current)
	void Search(ProgState& ps);     // Search through medias using the specified token, leaves vector unchanged.
	void Delete(ProgState& ps);     // Delete medias given a specified search key
	void Print(ProgState& ps);      // Prints out the table header and content for all medias.
	void Quit(ProgState& ps);       // Quits program as long as additional arguments aren't accidentally passed.
	void Add(ProgState& ps);        // Add different types of media, using Derived::usercreated() to instantiate.
	void Toggle(ProgState& ps);     // Toggle the visibility of the selected column
	void EnableCols(ProgState& ps); // Enable visibility of all columns
	void Default(ProgState& ps);    // Copies from defaults into current.
	void Clear(ProgState& ps);      // Clear all medias (TODO: Implement as wildcard * in delete command!)
	void Help(ProgState& ps);       // Prints command keywords, arguments, and descriptions

	const std::unordered_map<cstrkey, CommandDefinition> cmd_map = {
		{       {"quit"}, { Quit,       "", "Ends the program." }},
		{      {"print"}, { Print,      "", "Lists all the media." }},
		{       {"size"}, { Size,       "", "Prints out the size of default media and current media groups." }},
		{       {"help"}, { Help,       "", "this" }},
		{       {"sort"}, { Sort,       "[var]", "Sorts the media by the given variable (type, title, year...) (Ascending)" }},
		{     {"search"}, { Search,     "[keyword]", "Search through media for given keyword." }},
		{     {"delete"}, { Delete,     "[mode] [keyword]", "Remove media matching the given (type, search) and (type/keyword) pair." }}, 
		{    {"default"}, { Default,    "", "Resets media back to default. Deletes new entries and restores removed defaults." }},
		{        {"add"}, { Add,        "[type]", "Add media of specified type, will prompt for properties and preview." }}, 
		{     {"toggle"}, { Toggle,     "[column]", "Toggle the visibility of specified column."}},
		{ {"enablecols"}, { EnableCols, "", "Enables visibility of all columns."}},
		{      {"clear"}, { Clear,      "", "Clears the media list. Removes all medias." }},
	};
}
