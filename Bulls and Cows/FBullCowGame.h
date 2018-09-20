#pragma once
#include <string>
#include <set>
#define TSet std::set

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0, Cows = 0;
};

enum class EGuessStatus { OK, NotIsogram, WrongLength };
enum class EResetStatus { OK, NoHiddenWord };

class FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString guess) const; //TODO make a more rich return value

	void Reset(); //TODO make a more rich return value
	//counts bulls & cows, increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(const FString&);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	bool IsIsogram(FString word) const;
	bool bGameIsWon;
	FString MyHiddenWord;
};
