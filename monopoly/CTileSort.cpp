#include "CTileSort.h"

#include "CGo.h"
#include "CFreeParking.h"
#include "CJail.h"
#include "CGoToJail.h"
#include "CTax.h"
#include "CUtility.h"
#include "CStation.h"
#include "CChance.h"
#include "CChest.h"
#include "CProperty.h"
//other tiles that can be used

CTile* pNewTile(ETileType tType, istream& file)
{
	CTile* sqPtr = nullptr;

	//check which class it should be
	switch (tType)
	{
	case ETileType::Property:
		sqPtr = new CProperty(file); 
		break;
	case ETileType::Utility:
		sqPtr = new CUtility(file);
		break;
	case ETileType::Station:
		sqPtr = new CStation(file);
		break;
	case ETileType::Go:
		sqPtr = new CGo(file);
		break;
	case::ETileType::Jail:
		sqPtr = new CJail(file);
		break;
	case::ETileType::GoToJail:
		sqPtr = new CGoToJail(file);
		break;
	case::ETileType::Chance:
		sqPtr = new CChance(file); 
		break;
	case::ETileType::CommunityChest:
		sqPtr = new CChest(file); 
		break;
	case::ETileType::FreeParking:
		sqPtr = new CFreeParking(file);
		break;
	case::ETileType::Tax:
		sqPtr = new CTax(file);
		break;
	default:
		break;
	}
	return sqPtr;
}
