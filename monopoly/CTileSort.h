#include "CTile.h"
#include "Header.h"
#pragma once

enum class ETileType : int
{
	//types of tile

	Property = 1,
	Utility = 2,
	Station = 3,
	Go = 4,
	Jail = 5,
	GoToJail = 6,
	Chance = 7,
	CommunityChest = 8,
	FreeParking = 9, 
	Tax = 10
};


CTile* pNewTile(ETileType tType, istream& file);

