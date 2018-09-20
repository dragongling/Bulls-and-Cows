#pragma once
#include "UnrealStructures.h"
#include <fstream>
#include <random>

class FWordsDictionary
{
public:
	FWordsDictionary();
	bool ReadFromFile(const FString& FilePath);
	FString GetRandomWord() const;
private:
	int32 WordCount;
	FString Words;
};

