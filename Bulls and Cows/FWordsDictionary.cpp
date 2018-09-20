#include "stdafx.h"
#include "FWordsDictionary.h"

FWordsDictionary::FWordsDictionary()
{

}

bool FWordsDictionary::ReadFromFile(const FString & FilePath)
{
	std::fstream File;
	File.open(FilePath);
	if(!File.is_open())
		return false;
	std::getline(File, Words);
	File.close();
	WordCount = Words.length() / 4;
	return true;
}

FString FWordsDictionary::GetRandomWord() const
{
	const int32 WORD_LENGTH = 4;
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_int_distribution<int32> dist{ 0, WordCount - 1 };
	int32 WordIndex = dist(re);
	int32 WordOffset = WordIndex * WORD_LENGTH;
	return Words.substr(WordOffset, WORD_LENGTH);
}
