// Jeff McMillan 10-21-2022
// CPP Classes assignment

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "media.h"
#include "videogame.h"
#include "movie.h"
#include "music.h"

#define TRYRETCATCH(PTR, MTYPE) try { MTYPE* tp = dynamic_cast<MTYPE*>(PTR); if (tp!=0) return MediaType::MTYPE; } catch (...) {}
MediaType getType(Media* m) {
	TRYRETCATCH(m, Videogame);
	TRYRETCATCH(m, Movie);
	TRYRETCATCH(m, Music);
	return MediaType::UnknownType;
}
#undef TRYRETCATCH
#define CASERET(MTYPE) case MediaType::MTYPE: return #MTYPE;
const char* getMediaTypeStr(const MediaType &mt) {
	switch (mt) {
	CASERET(Videogame);
	CASERET(Movie);
	CASERET(Music);
	CASERET(UnknownType);
	default: return "INVALID ENUM VALUE!";		
	}
}
#undef CASERET

int main() {
	std::vector<Media*> medias = {
		new Videogame("Super Mario 64", 1996, "Nintendo", 9.8f),
		new Videogame("Rocket League", 2015, "Psyonix", 9.3f),
		new Videogame("Skate 3", 2010, "Black Box", 8.0f),
		new Videogame("Factorio", 2020, "Wube Software", 9.1f),
		new Videogame("Terraria", 2011, "Re-Logic", 8.5f),
		new Videogame("Minecraft", 2011, "Mojang", 10.0f),
		new Videogame("Fortnite", 2017, "Epic Games", 9.2f),
		new Videogame("Counter-Strike: Global Offensive", 2012, "Valve", 9.0f),
		new Videogame("Valorant", 2020, "Riot Games", 6.8f),
		new Videogame("Team Fortress 2", 2007, "Valve", 9.4f),
		new Videogame("Garry's Mod", 2006, "Facepunch Studios", 9.7f),
		new Videogame("The Escapists", 2015, "Mouldy Toof Studios", 8.3f),
		new Videogame("Portal", 2007, "Valve", 9.6f),
		new Videogame("Mirror's Edge", 2009, "DICE", 7.8f),
		new Videogame("Battlefield 4", 2013, "DICE", 9.0f),
		new Videogame("Grand Theft Auto V", 2013, "Rockstar Games", 9.8f),
		new Videogame("Sea of Thieves", 2018, "Rare", 8.5f),
		new Videogame("No Man's Sky", 2016, "Hello Games", 7.1f),
		new Videogame("Subnautica", 2014, "Unknown Worlds", 9.7f),
		new Videogame("Breath of the Wild", 2017, "Nintendo", 9.9f),
		new Videogame("Wii Sports", 2006, "Nintendo", 9.6f),
		new Videogame("Mario Kart: Double Dash!!", 2003, "Nintendo", 9.6f),
		new Videogame("ATV Offroad Fury", 2001, "Sony", 8.7f),
		new Videogame("Guitar Hero II", 2006, "Harmonix", 8.9f),
		new Videogame("The Simpsons: Road Rage", 2001, "Radical Entertainment", 4.3f),
		new Videogame("Spider-Man", 2000, "Treyarch", 9.1f),
		new Videogame("GoldenEye 007", 1997, "Rare", 9.5f),
		new Videogame("NBA Jam", 1993, "Midway / Iguana", 9.9f),
		new Videogame("Gran Turismo", 1997, "Sony", 9.2f),
		new Videogame("Star Fox 64", 1997, "Nintendo", 9.3f),
		new Videogame("Pokemon Red and Blue", 1996, "Game Freak", 9.4f),
		new Videogame("Halo: Combat Evolved", 2001, "Microsoft", 9.2f),
		new Videogame("Half-Life 2", 2004, "Valve", 10.0f),
		new Videogame("Halo: Reach", 2010, "Bungie", 9.8f),

		new Music("Hip Hop", 2000, "Dead Prez",  "Loud Records", Duration(0,3,54)),
		new Music("Redemption Song", 1984, "Bob Marley", "Island Def Jam", Duration(0,3,47)),
		new Music("Life Rolls On", 2015, "Slightly Stoopid", "Stoopid Records", Duration(0,3,39)),
		new Music("When It's Over", 1999, "Sugar Ray", "RT Industries", Duration(0,3,38)),
		new Music("Hurts So Good", 1982, "John Mellencamp", "Island Def Jam", Duration(0,3,38)),
		new Music("Feel The Rush", 2007, "Shaggy", "Ministry of Sound", Duration(0,3,6)),
		new Music("Spirit In The Sky", 1969, "Norman Greenbaum", "Craft Recordings", Duration(0,4,2)),
		new Music("Burden In My Hand", 1993, "Sound Garden", "UMG Recordings", Duration(0,4,50)),
		new Music("Easy", 1977, "The Commodores", "Motown Records", Duration(0,4,16)),
		new Music("Say Hey (I Love You)", 2008, "Michael Franti", "Spearhead", Duration(0,3,55)),
		new Music("Can't You See", 1973, "Marshall Tucker Band", "MT Industries", Duration(0,6,5)),
		new Music("Candle In The Wind", 1973, "Elton John", "This Record Company", Duration(0,3,48)),
		new Music("She's Gone", 1978, "Bob Marley", "Island Def Jam", Duration(0,2,25)),
		new Music("Blow Ya Mind", 2007, "Styles P", "KOCH Records", Duration(0,3,34)),
		new Music("You Ain't Seen Nothing Yet", 1974, "Bachman-Turner Overdrive", "Mercury Records", Duration(0,3,54)),
		new Music("Against the Wind", 1980, "Bob Seger", "Hideout Records", Duration(0,5,33)),
		new Music("After Forever", 1971, "Black Sabbath", "Warner Records", Duration(0,5,26)),
		new Music("Paranoid", 1970, "Black Sabbath", "Warner Records", Duration(0,2,48)),
		new Music("Baba O'Riley", 1971, "The Who", "Geffen Records", Duration(0,4,59)),
		new Music("Tennessee Whiskey", 2015, "Chris Stapleton", "Mercury Records", Duration(0,4,53)),
		new Music("Sarah", 2012, "Alex G", "Lucky Number", Duration(0,2,56)),
		new Music("Born In the U.S.A.", 1984, "Bruce Springsteen", "Bruce Springsteen", Duration(0,4,39)),
		new Music("Unwritten", 2004, "Natasha Bedingfield", "Sony", Duration(0,4,19)),
		new Music("Still Tippin'", 2004, "Mike Jones", "Warner Records", Duration(0,4,31)),
		new Music("Slide", 1998, "The Goo Goo Dolls", "Warner Records", Duration(0,3,32)),
		new Music("Listen to the Music", 1976, "The Doobie Brothers", "Warner MG", Duration(0,4,48)),
		new Music("Black Water", 1976, "The Doobie Brothers", "Warner MG", Duration(0,4,20)),
		new Music("Daughter", 1993, "Pearl Jam", "Sony", Duration(0,3,55)),
		new Music("Still Fly", 2002, "Big Tymers", "Cash Money Records", Duration(0,5,35)),
		new Music("Ain't Got No Haters", 2018, "Ice Cube", "Lench Mob Records", Duration(0,3,26)),
		new Music("Glorious Morning", 2015, "Waterflame", "Waterflame", Duration(0,1,52)),
		new Music("Night Moves", 1976, "Bob Seger", "Hideout Records", Duration(0,5,24)),
		new Music("The Middle", 2001, "Jimmy Eat World", "Dreamworks", Duration(0,2,45)),
		new Music("Master of Puppets", 1986, "Metallica", "Blackened Recordings", Duration(0,8,35)),
		new Music("The Day I Tried to Live", 1994, "Soundgarden", "A&M Records", Duration(0,5,20)),
		new Music("Black Hole Sun", 1994, "Soundgarden", "A&M Records", Duration(0,5,18)),
		new Music("Karma Chameleon", 1983, "Boy George", "Virgin Records", Duration(0,4,1)),
		new Music("Harder Than You Think", 2007, "Public Enemy", "SLAMjamz", Duration(0,4,9)),
		new Music("Ante Up", 2000, "M.O.P.", "Loud Records", Duration(0,4,8)),
		new Music("Go Crazy", 2005, "Jeezy", "Island Def Jam", Duration(0,4,13)),
		new Music("All About U", 1993, "2Pac", "Death Row Records", Duration(0,4,28)),
		new Music("2am", 2007, "Slightly Stoopid", "Stoopid Records", Duration(0,4,59)),
		new Music("Let the Beat Build", 2008, "Lil Wayne", "Cash Money Records", Duration(0,5,9)),
		new Music("Return of the Mack", 1996, "Mark Morrison", "Warner Music UK", Duration(0,3,33)),
		new Music("I Wish", 1995, "Skee-Lo", "Volcano Entertainment", Duration(0,4,9)),
		new Music("Fly", 1997, "Sugar Ray", "RT Industries", Duration(0,4,4)),
		new Music("Someday", 1999, "Sugar Ray", "RT Industries", Duration(0,4,3)),
		new Music("Dancing in the Moonlight", 1972, "Toploader", "Sony", Duration(0,3,52)),
		new Music("Margaritaville", 1977, "Jimmy Buffett", "UMG Recordings", Duration(0,4,10)),
		new Music("Stolen Dance", 2013, "Milky Chance", "Lichtdicht Records", Duration(0,5,13)),
		new Music("Island In The Sun", 2001, "Weezer", "Geffen Records", Duration(0,3,20)),
		new Music("TEMPTATION", 2017, "Joey Bada$$", "Pro Era", Duration(0,4,4)),
		new Music("Santeria", 1996, "Sublime", "Gasoline Alley", Duration(0,3,2)),
		new Music("What I Got", 1996, "Sublime", "Gasoline Alley", Duration(0,2,50)),
		new Music("Chicken Fried", 2008, "Zac Brown Band", "Home Grown Music", Duration(0,3,58)),
		new Music("I Won't Back Down", 1989, "Tom Petty", "Tom Petty", Duration(0,2,55)),
		new Music("Mr. Jones", 1993, "Counting Crows", "Geffen Records", Duration(0,4,32)),
		new Music("Hey Soul Sister", 2009, "Train", "Sony", Duration(0,3,36)),
		new Music("Semi-Charmed Life", 1997, "Third Eye Blind", "Elektra Entertainment", Duration(0,4,28)),
		new Music("Jumper", 1997, "Third Eye Blind", "Elktra Entertainment", Duration(0,4,33)),
		new Music("Sweet Caroline", 1969, "Neil Diamond", "Capitol Records", Duration(0,3,21)),
		new Music("Ain't It Fun", 2013, "Paramore", "Atlantic Recording", Duration(0,4,56)),
		new Music("Over", 2010, "Drake", "Young Money", Duration(0,3,53)),
		new Music("Upside Down", 2005, "Jack Johnson", "Brushfire Records", Duration(0,3,28)),
		new Music("Brandy", 1972, "Looking Glass", "Sony", Duration(0,3,9)),
		new Music("1979", 1995, "The Smashing Pumpkins", "Virgin Records", Duration(0,4,26)),
		new Music("Supersoaker", 2013, "Kings of Leon", "Kings of Leon", Duration(0,3,50)),
		new Music("Isn't She Lovely", 1976, "Stevie Wonder", "Motown Records", Duration(0,6,34)),
		new Music("Now Or Never", 2012, "Kendrick Lamar", "Aftermath Records", Duration(0,4,17)),
		new Music("She Will Be Loved", 2002, "Maroon 5", "Interscope Records", Duration(0,4,18)),
		new Music("Women In Love", 1979, "Van Halen", "Warner Records", Duration(0,4,9)),
		new Music("Dancing In The Street", 1982, "Van Halen", "Warner Records", Duration(0,3,45)),
		new Music("Stone In Love", 1981, "Journey", "Sony", Duration(0,4,25)),
		new Music("The Spins", 2010, "Mac Miller", "Rostrum Records", Duration(0,3,15)),
		new Music("Over the Hills and Far Away", 1973, "Led Zeppelin", "Atlantic Recording", Duration(0,4,50)),
		new Music("Down Under", 1981, "Men At Work", "CBS", Duration(0,3,42)),
		new Music("Who Can It Be Now?", 1981, "Men At Work", "CBS", Duration(0,3,21)),
		new Music("Hey Ya!", 2003, "Outkast", "Arista Records", Duration(0,3,55)),
		new Music("The Sweet Escape", 2006, "Gwen Stefani", "Interscope Records", Duration(0,4,6)),
		new Music("Rock and Roll All Nite", 1975, "Kiss", "Island Def Jam", Duration(0,2,46)),
		new Music("Little Guitars", 1982, "Van Halen", "Warner Records", Duration(0,3,47)),
		new Music("Dance the Night Away", 1979, "Van Halen", "Warner Records", Duration(0,3,9)),
		new Music("Shake Me Down", 2010, "Cage the Elephant", "JIVE Records", Duration(0,3,31)),
		new Music("Shine", 1993, "Collective Soul", "Craft Recordings", Duration(0,5,6)),
		new Music("Mellow Mood", 2003, "Slightly Stoopid", "Surfdog", Duration(0,4,40)),

		new Movie("Meet the Robinsons", 2007, "Stephen J. Anderson", Duration(1,35,0),6.8f),
		new Movie("Catch Me If You Can", 2002, "Steven Spielberg", Duration(2,21,0),8.1f),
		new Movie("Hoodwinked", 2005, "Cory Edwards", Duration(1,20,0),6.5f),		
		new Movie("Good Will Hunting", 1997, "Gus Van Sant", Duration(2,6,0),4.3f),
		new Movie("The Pursuit of Happyness", 2006, "Gabriele Muccino", Duration(1,57,0),8.0f),
		new Movie("Hitch", 2005, "Andy Tennant", Duration(1,58,0),6.6f),
		new Movie("The Intouchables", 2011, "Olivier Nakache", Duration(1,52,0),8.5f),		
		new Movie("Top Gun: Maverick", 2022, "Joseph Kosinski", Duration(2,11,0), 8.4f),
		new Movie("Tower Heist", 2011, "Brett Ratner", Duration(1,44,0), 6.2f),
		new Movie("Top Gun", 1986, "Tony Scott", Duration(1,50,0),6.9f),
		new Movie("Office Space", 1999, "Mike Judge", Duration(1,29,0),7.7f),
		new Movie("The Usual Suspects", 1995, "Bryan Singer", Duration(1,46,0),8.5f),
		new Movie("Green Book", 2018, "Peter Farrelly", Duration(2,10,0),8.2f),
		new Movie("Whiplash", 2014, "Damien Chazelle", Duration(1,46,0),8.5f),
		new Movie("Ford v Ferrari", 2019, "James Mangold", Duration(2,32,0),8.1f),
		new Movie("The Boondock Saints", 1999, "Troy Duffy", Duration(1,48,0),7.7f),
		new Movie("Fight Club", 1999, "David Fincher", Duration(2,19,0), 8.8f),
		new Movie("End of Watch", 2012, "David Ayer", Duration(1,49,0), 7.6f),
		new Movie("Four Lions", 2010, "Christopher Morris", Duration(1,37,0), 7.3f),
	};

	printf("Media Count: %i\n", medias.size());

	const int headw = 11;
	#define PRINTHEADER(TYPE) printf("%*s ", headw, #TYPE); TYPE::printHeader(); printf("\n");
	PRINTHEADER(Videogame);
	PRINTHEADER(Music);
	PRINTHEADER(Movie);
	printf("\n");
	PRINTHEADER(Media);
	
	for (std::vector<Media*>::iterator it = medias.begin();it!=medias.end();++it)
	{
		Media* mptr = *it;
		MediaType mt = getType(mptr);
	
		printf("%*s ", headw, getMediaTypeStr(mt));	
		mptr->print();
		printf("\n");
	}

	return 0;
}
