#include "stdafx.h"
#include "FBullCowGameCLI.h"

void FBullCowGameCLI::StartMainGameLoop()
{
	bPlayAgain = false;
	//TODO::Read words file
	if (!Dictionary.ReadFromFile(DICTIONARY_PATH))
	{
		std::cout << "Error: file \"" << DICTIONARY_PATH << "\" not found." << std::endl;
		return;
	}
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
}

void FBullCowGameCLI::PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << std::endl;
	std::cout << 
		"          }   {         ___            \n"
		"          (o o)        (o o)           \n"
		"   /-------\\ /          \\ /-------\\ \n"
		"  / | BULL |O            O| COW  | \\  \n"
		" *  |-,--- |              |------|  *  \n"
		"    ^      ^              ^      ^     \n"
		<< std::endl;
}

void FBullCowGameCLI::PlayGame()
{
	std::random_device rd;
	std::default_random_engine re(rd());
	HiddenWord = Dictionary.GetRandomWord(re, 7);
	std::cout << HiddenWord << std::endl;
	BCGame.Reset(HiddenWord);
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n" << std::endl;
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText ValidGuess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(ValidGuess);
		std::cout << "\nBulls = " << BullCowCount.Bulls << ", Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	PrintGameSummary();
}

FText FBullCowGameCLI::GetValidGuess()
{
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
		case EGuessStatus::RepeatingGuess:
			std::cout << "\nYou already tried that word";
			break;
		default:
			return Guess;
		}
		std::cout << ".\n\nPlease try again: ";
	}
}

bool FBullCowGameCLI::AskToPlayAgain()
{
	std::cout << "Enter 'y' if you wanna play again: ";
	FText answer;
	std::getline(std::cin, answer);
	std::cout << std::endl;
	return !answer.empty() && (answer[0] == 'y' || answer[0] == 'Y');
}

void FBullCowGameCLI::PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You won!\n" << std::endl;
	}
	else
	{
		std::cout << "The word was \"" << HiddenWord << "\". Better luck next time!\n" << std::endl;
	}
}
