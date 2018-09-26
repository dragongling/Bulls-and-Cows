#pragma once
#include "UnrealStructures.h"

class FASCIIArt
{
public:
	FASCIIArt(const FString& Art, const FString& Authors);

	const FString& GetAuthors() const;
	const FString& GetArt() const;
private:
	FString Art;
	FString Authors;
};