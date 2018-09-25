#pragma once
#include "UnrealStructures.h"

struct FBullCowCount
{
	int32 Bulls = 0, Cows = 0;
};

enum class EGuessStatus { OK, NotIsogram, WrongLength, RepeatingGuess };
enum class EResetStatus { OK, NoHiddenWord };

/**
 * Game logic for "Bulls and Cows" game
 */
class FBullCowGame
{
public:
	const FString DEFAULT_HIDDEN_WORD = "planet";
	const int32 WordLengthToMaxTries[4]{ 7,10,16,20 };

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
	bool bGameIsWon;
	FString HiddenWord;
	TSet<FString> GuessesTried;

	bool IsIsogram(const FString& Guess) const;
	FBullCowCount CountBullsAndCows(const FString& Word) const;
};
