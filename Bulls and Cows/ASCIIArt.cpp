#include "stdafx.h"
#include "ASCIIArt.h"

FASCIIArt::FASCIIArt(const FString& Art, const FString& Authors) : Authors(Authors) {
	this->Art = ParseIntoArray(Art, "\n");
}

FASCIIArt::FASCIIArt(const TArray<FString> Art, const FString & Authors) : Art(Art), Authors(Authors) {}

const FString& FASCIIArt::GetAuthors() const { return Authors; }

const FString FASCIIArt::GetArt() const 
{
	return Join(Art, "\n"); 
}
