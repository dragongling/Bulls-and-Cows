#include "stdafx.h"
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
    return 0;
}

void PrintIntro() {	
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n"
		<< "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n" << std::endl;
}

void PlayGame()
{
	BCGame.Reset("fusion");
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText ValidGuess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(ValidGuess);
		std::cout << "\nBulls = " << BullCowCount.Bulls << ", Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	PrintGameSummary();
}

FText GetValidGuess() {
	int32 TriesLeft = BCGame.GetMaxTries() - BCGame.GetCurrentTry() + 1;
	std::cout << std::to_string(TriesLeft) << (TriesLeft == 1 ? " try" : " tries") << " left. Enter your guess: ";
	FText Guess;
	while (true)
	{
		std::getline(std::cin, Guess);
		switch (BCGame.CheckGuessValidity(Guess))
		{
		case EGuessStatus::NotIsogram:
			std::cout << "\nNo repeating letters allowed";
			break;
		case EGuessStatus::WrongLength:
			std::cout << "\nWord should contain " << BCGame.GetHiddenWordLength() << " letters";
			break;
		default:
			return Guess;
		}
		std::cout << ".\n\nPlease try again: ";
	}
}

bool AskToPlayAgain()
{
	std::cout << "Enter 'y' if you wanna play again: ";
	FText answer;
	std::getline(std::cin, answer);
	std::cout << std::endl;
	return !answer.empty() && (answer[0] == 'y' || answer[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You won!\n" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time!\n" << std::endl;
	}
}
