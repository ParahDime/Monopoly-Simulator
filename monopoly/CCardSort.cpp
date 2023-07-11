#include "CCardSort.h"

#include "CCardEarn.h"
#include "CCardLose.h"
#include "CCardMove.h"
#include "CCardOutofJail.h"
#include "CCardJail.h"
#include "CCardRepair.h"
#include "CCardCollection.h"
//other tiles that can be used

CCard* pNewCard(ECardType tType, istream& file)
{
	CCard* sqPtr = nullptr;

	//check which class it should be
	switch (tType)
	{
	case ECardType::Earn:
		sqPtr = new CCardEarn(file);
		break;
	case ECardType::Lose:
		sqPtr = new CCardLose(file);
		break;
	case ECardType::Move:
		sqPtr = new CCardMove(file);
		break;
	case ECardType::FreeJailCard:
		sqPtr = new CCardOutofJail(file);
		break;
	case ECardType::GoToJail:
		sqPtr = new CCardJail(file);
		break;
	case ECardType::Repairs:
		sqPtr = new CCardRepair(file);
		break;
	case ECardType::Collection:
		sqPtr = new CCardCollection(file);
		break;
	default:
		break;
	}
	return sqPtr;
}
