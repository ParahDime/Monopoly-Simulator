#include "CCard.h"
#include "Header.h"
#pragma once
enum class ECardType : int
{
	//types of card
	Earn = 1,
	Lose = 2,
	Move = 3,
	FreeJailCard = 4,
	GoToJail = 5,
	Repairs = 6,
	Collection = 7


};


CCard* pNewCard(ECardType tType, istream& file);

