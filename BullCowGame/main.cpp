//This is main function only. Logic in other files

#include <iostream>
#include <string>

#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main()
{
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		
	} while (AskToPlayAgain());
	
	return 0;
}

void PrintIntro()
{
	std:: cout << "\n\nWelcome to Bulls and Cows a fun word game." << std:: endl;
	std:: cout << "Can you guess the " << BCGame.GetHidenWordLength();
	std:: cout << " letter isogram I'm thinking of" << std:: endl;
	return;
}

void PrintGameSummary()
{
	std:: cout << (BCGame.IsGameWon() ? "WELL DONE -- YOU WIN!\n" : "Better luck next time!\n" ) << std::endl;
}

void PlayGame()
{
	FText UserGuess;
	
	do {
		UserGuess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(UserGuess);
		
		if (!BCGame.IsGameWon())
			std:: cout << "Bulls " << BullCowCount.Bulls << ". Cows " << BullCowCount.Cows << std:: endl;
		
	} while(!BCGame.IsGameWon() &&  BCGame.GetCurrentTry() < BCGame.GetMaxTries());
	
	return;
}

FText GetValidGuess()
{
	EWordStatus Status = EWordStatus:: Invalid_status;
	FText Guess = "";
	
	do {
		std:: cout << "Try "<< BCGame.GetCurrentTry() <<". Enter a guess: ";
		getline(std:: cin, Guess);
		
		Status = BCGame.CheckGuessValidity(Guess);
		
		switch (Status)
		{
			case EWordStatus:: Wrong_length:
				std::cout << "Please enter a " << BCGame.GetHidenWordLength() << " letter word.\n";
				break;
				
			case EWordStatus:: Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n";
				break;
				
			case EWordStatus:: Not_lowercase:
				std::cout << "Please enter a word in only lowercase.\n";
				break;
				
			default:
				//Assuming the guess is valid
				break;
		}
		std::cout << std::endl;
		
	} while(Status != EWordStatus:: OK);
	
	return Guess;
}

bool AskToPlayAgain()
{
	do {
		std:: cout << "Do you want to play again with the same word (y/n)?" << std:: endl;
		FText Response = "";
		getline(std:: cin, Response);
		
		if ((Response[0] == 'y') || (Response[0] == 'Y'))
		{
			BCGame.Reset();
			return true;
		}
		else if ((Response[0] == 'n') || (Response[0] == 'N'))
			return false;
		
		else
			std:: cout << "Not sure what you meant by " << Response << "\n";
		
	} while (true);
}
