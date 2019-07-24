#pragma once
#include <time.h>

#include "pch.h"
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame(){Reset();}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon(int32 BullCount) const{	return BullCount ==GetHiddenWordLength();}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (GetHiddenWordLength() != Guess.length()) { return EGuessStatus::Wrong_Length; }
	else if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
	else if (RepeatedWord(Guess)) { return EGuessStatus::Repeated_Word; }
	else if (!OnlyLetters(Guess)) { return EGuessStatus::Wrong_Signs; }
	else { return EGuessStatus::OK; }
}

int32 FBullCowGame::GetHiddenWordLength() const {	return MyHiddenWord.length();}

//recieves a valid guess, increments turn count, and returns bulls & cows count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	++MyCurrentTry;
	FBullCowCount BullCowCount;

	int32 GuessLength = Guess.length();

	for (int32 HWChar = 0; HWChar != GetHiddenWordLength(); ++HWChar)
	{
		for (int32 GChar = 0; GChar != GuessLength; ++GChar)
		{
			if (MyHiddenWord[HWChar] == Guess[GChar])
			{
				if (HWChar == GChar)
				{
					++BullCowCount.Bulls;
				}
				else
				{
					++BullCowCount.Cows;
				}
			}
		}
	}

	return BullCowCount;
}

int32 FBullCowGame::GetMaxTries() const { 
	TMap <int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 10}, {5, 15}, {6, 20}, {7, 25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	srand(static_cast<unsigned int>(time(NULL)));
	int32 RandomWordIndex = rand() % HiddenWordsBank.size();

	MyCurrentTry = 1;
	MyHiddenWord = HiddenWordsBank[RandomWordIndex];
	EnteredGuesses.clear();
	return;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() < 2) { return true; }

	TMap <char, bool> LetterSeen;


	for (auto Letter : Guess) //run through the whole word
	{
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }	
	}

	return true;
}

void FBullCowGame::UpdateEnteredGuesses(FString Guess)
{
	EnteredGuesses.insert(EnteredGuesses.end(), Guess);
}

FString FBullCowGame::ChangeToLowercase(FString Guess) const
{
	for (int32 GLetterIndex =0; GLetterIndex !=Guess.length(); ++GLetterIndex)
	{
		char Letter = Guess[GLetterIndex];
		Guess[GLetterIndex] = tolower(Letter);
	}
	return Guess;
}

bool FBullCowGame::RepeatedWord(FString Guess) const
{

	for (int i = 0; i != EnteredGuesses.size(); ++i)
	{
		if (EnteredGuesses[i] == Guess) { return true; }
	}
	return false;
}

bool FBullCowGame::OnlyLetters(FString Guess) const
{
	for (auto Letter : Guess) 
	{
		if (!isalpha(Letter)) { return false; }
	}
	return true;
}
//
