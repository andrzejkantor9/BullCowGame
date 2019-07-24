#pragma once
#include "pch.h"
#include "View.h"

void FView::PrintIntro()
{
	BCGame.Reset();
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;

	std::cout << "        {|  |}          ___" << std::endl;
	std::cout << "        {|__|}         /   \\" << std::endl;
	std::cout << "       /     \\        /     \\" << std::endl;
	std::cout << "      ( 0   0 )      ( 0   0 )" << std::endl;
	std::cout << "       \\  _  /        \\  _  /" << std::endl;
	std::cout << "        -----          -----" << std::endl;
	std::cout << "        BULL            COW" << std::endl;
	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//plays a single game to completion
void FView::PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	FBullCowCount BullCowCount;
	while (!BCGame.IsGameWon(BullCowCount.Bulls) && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows;
		std::cout << std::endl;

		std::cout << std::endl;
	}
	PrintGameSummary(BullCowCount.Bulls);

	return;
}

bool FView::AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again with a different word (y/n)?\n";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

//loop continually untill the user gets a valid guess
FText FView::GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry;
		std::cout << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess : ";
		std::getline(std::cin, Guess);
		Guess = BCGame.ChangeToLowercase(Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
			std::cout << " length word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Repeated_Word:
			std::cout << "Please enter new word.\n\n";
			break;
		case EGuessStatus::Wrong_Signs:
			std::cout << "Please enter letters only.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	BCGame.UpdateEnteredGuesses(Guess);
	return Guess;
}

void FView::PrintGameSummary(int32 Bulls) const
{
	if (BCGame.IsGameWon(Bulls)) { std::cout << "Congratulations! You have won the game!\n"; }
	else { std::cout << "Bad luck, better luck next time.\n"; }
	return;
}
//
