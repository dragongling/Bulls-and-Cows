#pragma once
#include "UnrealStructures.h"
#include <fstream>
#include <random>

/**
 * Contains multiple fixed length isograms
 */
class FNLengthIsograms
{
public:
	FNLengthIsograms(const int32& IsogramLength);
	void ReadFromString(const FString& FilePath);
	FString GetRandomWord(std::default_random_engine& g) const;
private:
	int32 IsogramLength;
	int32 WordCount;
	FString Words;
};

