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

const FString FASCIIArt::GetBorderedArt() const
{
	int32 Width = GetWidth();
	std::stringstream ss;
	FString LeftRigthBorder = "#";
	FString UpDownBorder = "#";
	ss << Repeat(UpDownBorder, Width + 2 + LeftRigthBorder.size() * 2) << "\n";
	ss << LeftRigthBorder << std::string(Width + 2, ' ') << LeftRigthBorder << '\n';
	for (const auto& Line : Art)
	{
		ss << LeftRigthBorder << ' ' << Line << std::string(Width - Line.size() + 1,' ') << LeftRigthBorder << "\n";
	}
	ss << LeftRigthBorder << std::string(Width + 2, ' ') << LeftRigthBorder << '\n';
	ss << Repeat(UpDownBorder, Width + 2 + LeftRigthBorder.size() * 2) << "\n";
	return std::string(ss.str());
}

const int32 & FASCIIArt::GetWidth() const
{
	int32 Width = Art[0].size();
	for (const auto& Line : Art)
	{
		if (Line.size() > Width)
		{
			Width = Line.size();
		}
	}
	return Width;
}

const int32 & FASCIIArt::GetHeight() const
{
	return Art.size();
}
