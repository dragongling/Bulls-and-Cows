#pragma once
#include "UnrealStructures.h"
#include "FBullCowGame.h"
#include "IsogramsDictionary.h"

/**
 * Terminal client for "Bulls and Cows" game
 */
class FBullCowGameCLI
{
public:
	void StartMainGameLoop();
private:
	const FString DICTIONARY_PATH = "dictionary.txt";

	FString HiddenWord;
	FBullCowGame BCGame;
	FIsogramsDictionary Dictionary;

	bool bPlayAgain;

	void PrintIntro();
	void PrintASCIIArt();
	void PrintRules();

	void PlayGame();
	FText GetValidGuess();
	bool AskToPlayAgain();
	void PrintGameSummary();
};

