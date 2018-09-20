#pragma once
#include "UnrealStructures.h"
#include "NLengthIsograms.h"
#include <fstream>
#include <vector>

/**
 * Dictionary that 
 *   reads isograms of various lengths from file
 *   and provides them
 */
class FIsogramsDictionary
{
public:
	bool ReadFromFile(const FString& FilePath);
	FString GetRandomWord(std::default_random_engine& g, const int32 & Length) const;
private:
	const int32 STARTING_ISOGRAMS_LENGTH = 4;
	TArray<FNLengthIsograms> Isograms;
};

