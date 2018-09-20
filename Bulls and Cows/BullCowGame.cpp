#include "stdafx.h"
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planet";

	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;	
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WrongLength;
	}
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NotIsogram;
	}
	return EGuessStatus::OK; //TODO: make an actual error
}

//receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(const FString& Guess)
{
	//increment turn number
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	FString LoweredGuess = Guess;
	//loop through all letters in the guess
	for (int32 i = 0; i < Guess.length(); ++i)
	{
		char LoweredGuessChar = tolower(Guess[i]);
		if (LoweredGuessChar == MyHiddenWord[i])
		{
			BullCowCount.Bulls++;
		}
		else
		{
			for (int32 j = 0; j < GetHiddenWordLength(); ++j)
			{
				if (LoweredGuessChar == MyHiddenWord[j])
				{
					BullCowCount.Cows++;
					break;
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TSet<char> GuessCharacters{};
	for (const char& c : Guess)
	{
		if (GuessCharacters.find(c) == GuessCharacters.end())
		{
			GuessCharacters.insert(c);
		}
		else
		{
			return false;
		}
	}
	return true;
}
