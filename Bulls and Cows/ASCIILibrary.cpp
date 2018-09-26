#include "stdafx.h"
#include "ASCIILibrary.h"


bool FASCIILibrary::ReadFromFile(const FString & FilePath)
{
	std::fstream File;
	File.open(FilePath);
	if (!File.is_open())
		return false;
	while (!File.eof()) {
		FString Line, Author, CurrentArt;
		std::getline(File, Line);
		int32 ASCIIHeight = std::stoi(Line);
		std::getline(File, Author);
		for (int32 i = 0; i < ASCIIHeight; ++i) 
		{
			std::getline(File, Line);
			CurrentArt += Line + "\n";
		}
		Art.push_back(FASCIIArt{ CurrentArt, Author });
	}
	File.close();
	return true;
}

FASCIIArt FASCIILibrary::GetRandomArt(std::default_random_engine & g) const
{
	if (Art.size() == 0)
		return FASCIIArt{ R"(
          }   {         ___
          (o o)        (o o)
   /-------\ /          \ /-------\
  / | BULL |O            O| COW  | \
 *  |-,--- |              |------|  *
    ^      ^              ^      ^
)", "Ben" };
	std::uniform_int_distribution<std::size_t> dist{ 0, Art.size() - 1 };
	int32 ArtIndex = dist(g);
	return Art[ArtIndex];
}
