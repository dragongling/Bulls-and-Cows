#include "stdafx.h"
#include "FBullCowGameCLI.h"

void FBullCowGameCLI::StartMainGameLoop()
{
	bPlayAgain = false;
	if (!Dictionary.ReadFromFile(DICTIONARY_PATH))
	{
		std::cout << "Error: file \"" << DICTIONARY_PATH << "\" not found." << std::endl;
		return;
	}
	FASCIILibrary IntroArtLibrary;
	IntroArtLibrary.ReadFromFile("ASCIIArt.txt");
	std::random_device rd;
	std::default_random_engine re(rd());
	IntroArt = IntroArtLibrary.GetRandomArt(re);
	PrintIntro();
	do {		
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	PrintOutro();
}

void FBullCowGameCLI::PrintIntro()
{
	std::cout << IntroArt.GetArt() << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << std::endl;
	PrintRules();
	std::cout << std::endl;
}

void FBullCowGameCLI::PrintRules()
{
	std::cout <<
		"In this game, a bull is the correct letter in the correct position.\n"
		"A cow is the correct letter, but in the wrong position in the word.\n"
		"An isogram is a word with no more than one of each letter in it."
		<< std::endl;
}

void FBullCowGameCLI::PrintOutro() const
{
	std::cout << 
		"Thank you for playing the game!"
		"\nArt by " << IntroArt.GetAuthors() <<
		"\nCode by Alexander Slesarenko, 2018" 
		<< std::endl;
}

void FBullCowGameCLI::PlayGame()
{
	std::random_device rd;
	std::default_random_engine re(rd());
	int32 WordLength = ChooseWordLength();
	HiddenWord = Dictionary.GetRandomWord(re, WordLength);
	//std::cout << HiddenWord << std::endl; // Debugging only
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

int32 FBullCowGameCLI::ChooseWordLength()
{
	int32 WordLength = 0;
	do
	{
		std::cout << "Choose word length (4-7): ";
		FString Line;
		std::getline(std::cin, Line);
		try 
		{
			WordLength = std::stoi(Line);
		}
		catch (std::invalid_argument e) {}
	} while (WordLength < 4 || WordLength > 7);
	return WordLength;
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
