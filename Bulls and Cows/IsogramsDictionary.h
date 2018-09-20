#pragma once
#include "UnrealStructures.h"
#include "NLengthIsograms.h"
#include <fstream>
#include <vector>

class FIsogramsDictionary
{
public:
	bool ReadFromFile(const FString& FilePath);
	FString GetRandomWord(std::default_random_engine& g, const int32 & Length) const;
private:
	const int32 STARTING_ISOGRAMS_LENGTH = 4;
	std::vector<FNLengthIsograms> Isograms;
};

