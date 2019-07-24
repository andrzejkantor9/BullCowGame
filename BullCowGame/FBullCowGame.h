/*The game logic (no view code or user interaction)
The game is a single word guess based on Mastermind
*/

#pragma once
#include <string>
#include <map>
#include <vector>

//to make syntax Unreal friendly
#define TMap std::map
#define TArray std::vector
using FString = std::string;
using int32 = int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

/*
enumerator that contains various statuses of word that may beentered by the player*/
enum class EGuessStatus
{
	Invalid_Status,
	OK, 
	Not_Isogram,
	Wrong_Length,
	Repeated_Word, 
	Wrong_Signs,
};

/*
class that contains logic behind the bullcow game and public interface
*/
class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const; 
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon(int32) const;
	EGuessStatus CheckGuessValidity(FString) const; 
	FString ChangeToLowercase(FString) const;

	void UpdateEnteredGuesses(FString);
	FBullCowCount SubmitValidGuess(FString);
	void Reset(); 

private:
	//see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	TArray <FString> HiddenWordsBank{"cat", "axe", "plan", "able", "beat", "ride", "plane", "brain", "metal", "harpy", "script", "filmed", "planet", "timber", "solvent", "deposit", "germain"};
	TArray <FString> EnteredGuesses{};

	bool IsIsogram(FString) const; 
	bool RepeatedWord(FString) const;
	bool OnlyLetters(FString) const;
};
//
