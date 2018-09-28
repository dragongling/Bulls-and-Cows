#pragma once

using int32 = int;
using uint32 = unsigned int;

#include <string>
using FText = std::string;
using FString = std::string;

#include <set>
#define TSet std::set

#include <vector>
#define TArray std::vector

#include <map>
#define TMap std::map

#include <sstream>

TArray<FString> ParseIntoArray(FString s, const FString& delimiter);

FString Join(TArray<FString> Array, FString separator);