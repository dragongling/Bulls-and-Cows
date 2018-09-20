#include "stdafx.h"
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	CurrentTry = 1;
	MaxTries = DEFAULT_MAX_TRIES;	
	HiddenWord = DEFAULT_HIDDEN_WORD;
	bGameIsWon = false;
}

void FBullCowGame::Reset(const FString& NewHiddenWord)
{
	Reset();
	HiddenWord = NewHiddenWord;
}

EGuessStatus FBullCowGame::CheckGuessValidity(const FString& Guess) const
{
	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WrongLength;
	}
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NotIsogram;
	}
	return EGuessStatus::OK;
}

//receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(const FString& ValidGuess)
{
	//increment turn number
	CurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	FString LoweredGuess = ValidGuess;
	//loop through all letters in the guess
	for (int32 i = 0; i < ValidGuess.length(); ++i)
	{
		char LoweredGuessChar = tolower(ValidGuess[i]);
		if (LoweredGuessChar == HiddenWord[i])
		{
			BullCowCount.Bulls++;
		}
		else
		{
			for (int32 j = 0; j < GetHiddenWordLength(); ++j)
			{
				if (LoweredGuessChar == HiddenWord[j])
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

bool FBullCowGame::IsIsogram(const FString& Guess) const
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
