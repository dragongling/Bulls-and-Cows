#include "stdafx.h"
#include "FBullCowGame.h"

FString ToLower(const FString& Word);

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetMaxTries() const 
{
	return WordLengthToMaxTries[GetHiddenWordLength() - 4];
}

int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	CurrentTry = 1;
	HiddenWord = DEFAULT_HIDDEN_WORD;
	bGameIsWon = false;
	GuessesTried.clear();
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
	if (GuessesTried.find(Guess) != GuessesTried.end())
	{
		return EGuessStatus::RepeatingGuess;
	}
	return EGuessStatus::OK;
}

//receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(const FString& ValidGuess)
{
	CurrentTry++;
	FString LoweredGuess = ToLower(ValidGuess);
	GuessesTried.insert(LoweredGuess);
	FBullCowCount BullCowCount = CountBullsAndCows(LoweredGuess);
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

FBullCowCount FBullCowGame::CountBullsAndCows(const FString & Word) const
{
	FBullCowCount BullCowCount;
	for (int32 i = 0; i < Word.length(); ++i)
	{
		char LoweredGuessChar = tolower(Word[i]);
		if (Word[i] == HiddenWord[i])
		{
			BullCowCount.Bulls++;
		}
		else
		{
			for (int32 j = 0; j < GetHiddenWordLength(); ++j)
			{
				if (Word[i] == HiddenWord[j])
				{
					BullCowCount.Cows++;
					break;
				}
			}
		}
	}
	return BullCowCount;
}

FString ToLower(const FString& String)
{
	FString NewString = "";
	for (const char& c : String)
	{
		NewString += tolower(c);
	}
	return NewString;
}