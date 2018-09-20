#pragma once
#include "UnrealStructures.h"
#include "FBullCowGame.h"
#include "IsogramsDictionary.h"

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
	void PlayGame();
	FText GetValidGuess();
	bool AskToPlayAgain();
	void PrintGameSummary();
};

