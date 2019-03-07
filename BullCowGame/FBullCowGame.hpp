#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_length,
	Not_lowercase
};

class FBullCowGame
{
public :
	FBullCowGame();
	FBullCowGame(int32 max);
	
	//MARK:- Getters
	int32 GetMaxTries() const { return MyMaxTries; }
	int32 GetCurrentTry() const { return MyCurrentTry; }
	int32 GetHidenWordLength() const { return (int) MyHiddenWord.length(); }
	bool IsGameWon() const { return bGameIsWon; }
	
	void Reset(); //TODO:- Return somthing else then void
	EWordStatus CheckGuessValidity(FString);
	
	//some new type SubmitValidatGess()
	FBullCowCount SubmitValidGuess(FString Guess);
	
private :
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString word);
};
