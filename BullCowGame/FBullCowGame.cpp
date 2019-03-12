#include <iostream>
#include <string>
#include <algorithm>

#include "FBullCowGame.hpp"

using FString = std::string;
using int32 = int;

//MARK:- Construction
FBullCowGame::FBullCowGame(int32 max)
{
	MyCurrentTry = 1;
	MyMaxTries = max;
}

FBullCowGame::FBullCowGame() { Reset(); }

void FBullCowGame:: Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return;
}

EWordStatus FBullCowGame:: CheckGuessValidity(FString Guess) {
	if (!IsIsogram(Guess))
		return EWordStatus:: Not_Isogram;
	
	else if (!isLowercase(Guess))
		return EWordStatus:: Not_lowercase;
	
	else if (Guess.length() != GetHidenWordLength())
		return EWordStatus:: Wrong_length;
	
	else
		return EWordStatus:: OK;
}

bool FBullCowGame:: IsIsogram(FString word)
{
	std::sort(word.begin(), word.end());
	for (int i = 1; i < word.size(); i++)
		if (word[i] == word[i-1])
			return false;
	return true;
}

bool FBullCowGame:: isLowercase(FString word)
{
	for (int i = 0; i < word.length(); i++)
		if ((int) word[i] < 97)
			return false;

	return true;
}

FBullCowCount FBullCowGame:: SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	
	FBullCowCount BullCowCount;
	int32 length = (int) MyHiddenWord.length();
	
	for (int32 i = 0; i < length; i++)
		for (int32 j = 0; j < length; j++)
			if (Guess[j] == MyHiddenWord[i]) {
				(j == i) ? BullCowCount.Bulls++ : BullCowCount.Cows++;
				break;
			}
	
	if (BullCowCount.Bulls == GetHidenWordLength())
		bGameIsWon = true;
	
	return BullCowCount;
}
