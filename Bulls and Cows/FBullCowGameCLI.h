#pragma once
#include "UnrealStructures.h"
#include "FBullCowGame.h"
#include "IsogramsDictionary.h"
#include "ASCIIArt.h"

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
	const FASCIIArt IntroArt{ R"(
          }   {         ___
          (o o)        (o o)
   /-------\ /          \ /-------\
  / | BULL |O            O| COW  | \
 *  |-,--- |              |------|  *
    ^      ^              ^      ^
)", "Ben" };

	bool bPlayAgain;

	void PrintIntro();
	void PrintRules();
	void PrintOutro() const;

	void PlayGame();
	int32 ChooseWordLength();
	FText GetValidGuess();
	bool AskToPlayAgain();
	void PrintGameSummary();
};

