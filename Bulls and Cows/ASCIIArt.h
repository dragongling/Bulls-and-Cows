#pragma once
#include "UnrealStructures.h"

class FASCIIArt
{
public:
	FASCIIArt(const FString& Art, const FString& Authors);
	FASCIIArt(const TArray<FString> Art, const FString& Authors);

	const FString& GetAuthors() const;
	const FString GetArt() const;
private:
	TArray<FString> Art;
	FString Authors;
};