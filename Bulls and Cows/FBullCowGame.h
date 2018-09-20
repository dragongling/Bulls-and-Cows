#pragma once
#include "UnrealStructures.h"

struct FBullCowCount
{
	int32 Bulls = 0, Cows = 0;
};

enum class EGuessStatus { OK, NotIsogram, WrongLength };
enum class EResetStatus { OK, NoHiddenWord };

class FBullCowGame
{
public:
	static const int32 DEFAULT_MAX_TRIES = 8;
	const FString DEFAULT_HIDDEN_WORD = "planet";

	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(const FString& Guess) const;

	void Reset();
	void Reset(const FString& NewHiddenWord);

	//counts bulls & cows, increases try #
	FBullCowCount SubmitValidGuess(const FString& ValidGuess);

private:
	int32 CurrentTry;
	int32 MaxTries;
	bool bGameIsWon;
	FString HiddenWord;

	bool IsIsogram(const FString& Guess) const;
};
