#pragma once
#include "UnrealStructures.h"
#include "FBullCowGame.h"

class FBullCowGameCLI
{
public:
	void StartMainGameLoop();
private:
	FBullCowGame BCGame;
	bool bPlayAgain;

	void PrintIntro();
	void PlayGame();
	FText GetValidGuess();
	bool AskToPlayAgain();
	void PrintGameSummary();
};

