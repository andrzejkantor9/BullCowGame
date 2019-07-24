#pragma once
#include <iostream>
#include "FBullCowGame.h"

//to make syntax more Unreal friendly
#define TArray std::vector
using int32 = int;
using FText = std::string;

class FView
{
public:
	void PrintIntro();
	void PlayGame();
	bool AskToPlayAgain();
private:
	FText GetValidGuess();
	void PrintGameSummary(int32 Bulls) const;
	FBullCowGame BCGame; 
};
//
