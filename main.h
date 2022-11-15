

MediaType getMediaTypeFromPtr(Media* m);
const char* getMediaTypeStr(const MediaType &mt);

// Store the width of columns, whether columns are visible,
// Static members also determine left-align, number of columns, column titles, and enums.
struct TableState {
public:
	static constexpr int COL_CT = 7;
	static constexpr bool COL_LA[COL_CT]     = {false, false, false, true, false, false, true };
	// TODO: Unify this definition and the names within map in Media::getStrVarMap();
	static constexpr const char* COL_NAMES[COL_CT] = {"Type", "Title", "Year", "Creator", "Rating", "Duration", "Publisher" };
	static constexpr Media::Var COL_VARS[COL_CT] = { Media::Var::Type, Media::Var::Title, Media::Var::Year,
		 Media::Var::Creator, Media::Var::Rating, Media::Var::Duration, Media::Var::Publisher };
	int COL_WIDTH[COL_CT] = { 25, 25, 4, 25, 6, 9, 25 };
	bool COL_ENABLED[COL_CT] = { false, true, true, true, true, true, true };
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
	const std::string args;
	const std::string help;	
};