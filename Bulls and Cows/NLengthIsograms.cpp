#include "stdafx.h"
#include "NLengthIsograms.h"

FNLengthIsograms::FNLengthIsograms(const int32 & IsogramLength) : IsogramLength(IsogramLength) {}

void FNLengthIsograms::ReadFromString(const FString & String)
{
	Words = String;
	WordCount = Words.length() / IsogramLength;
}

FString FNLengthIsograms::GetRandomWord(std::default_random_engine& g) const
{
	std::uniform_int_distribution<int32> dist{ 0, WordCount - 1 };
	int32 WordIndex = dist(g);
	int32 WordOffset = WordIndex * IsogramLength;
	return Words.substr(WordOffset, IsogramLength);
}
