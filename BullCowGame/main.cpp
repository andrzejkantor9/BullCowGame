/*This is console executable, that makes use of the BullCow class
This acts as the viev in MVP pattern and is responsible for all
user interaction. For game logic see BullCowGame class.
*/
#pragma once
#include "pch.h"
#include <iostream>
#include <string>

#include "FBullCowGame.h"
#include "View.h"

int main()
{
	bool bPlayAgain = false;
	FView View;
	
	do
	{
		View.PrintIntro();
		View.PlayGame();
		bPlayAgain = View.AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}
//
