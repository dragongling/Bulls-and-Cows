#include "stdafx.h"
#include "UnrealStructures.h"

TArray<FString> ParseIntoArray(FString s, const FString& delimiter)
{
	TArray<FString> result;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		result.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	return result;
}

FString Join(TArray<FString> Array, FString separator)
{
	std::stringstream ss;
	for (const auto& Line : Array)
	{
		ss << Line << separator;
	}
	return std::string(ss.str());
}