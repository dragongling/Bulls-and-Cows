#pragma once
#include "UnrealStructures.h"
#include <random>
#include <fstream>
#include "ASCIIArt.h"

class FASCIILibrary
{
public:
	bool ReadFromFile(const FString& FilePath);
	FASCIIArt GetRandomArt(std::default_random_engine& g) const;
private:
	TArray<FASCIIArt> Art;
};

