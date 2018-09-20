#include "stdafx.h"
#include "IsogramsDictionary.h"

bool FIsogramsDictionary::ReadFromFile(const FString & FilePath)
{
	std::fstream File;
	File.open(FilePath);
	if (!File.is_open())
		return false;
	for (int IsogramLength = STARTING_ISOGRAMS_LENGTH; !File.eof(); ++IsogramLength) {
		Isograms.push_back(FNLengthIsograms{ IsogramLength });
		FString Line;
		std::getline(File, Line);
		Isograms.back().ReadFromString(Line);
	}
	File.close();
	return true;
}

FString FIsogramsDictionary::GetRandomWord(std::default_random_engine& g, const int32 & Length) const
{
	return Isograms[Length - STARTING_ISOGRAMS_LENGTH].GetRandomWord(g);
}
