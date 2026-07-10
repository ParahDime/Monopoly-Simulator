#include "CUtility.h"

CUtility::CUtility(istream& file) : CTile(file)
{
	file >> *this;
	mOwner = -1;
	mMortgage = false;
}

CUtility::~CUtility()
{
}

void CUtility::BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile("\n[ Utility Bought ]\n[ Name ]: " + mName + "\n[ Price ]: " + char(156) + to_string(mPrice) + "\n");

	mOwner = position;

	//player pays money
	aPlayers[position]->TakeMoney(mPrice, cGame);
}

void CUtility::MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position)
{
	if (mMortgage == false)
	{
		mMortgage = true;
		aPlayers[position]->GiveMoney(mPrice / 2, cGame);
	}
	else
	{
		mMortgage = false;
	}	
}

void CUtility::ResetTile()
{
	mOwner = -1;
	mMortgage = false;
}

int CUtility::GetOwner()
{
	return mOwner;
}

void CUtility::PayBill(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pDieRoll, unique_ptr<int>& pTypeOwned, unique_ptr<Logger>& ioLog)
{
	//take the value of the role
	*pDieRoll = (*pDieRoll * *pTypeOwned) * 4;

	//difficulty multiplier
	if (position == 0)
	{
		*pDieRoll *= cGame->GetMultiplier();
	}

	ioLog->writeToFile("\n[ Rent ]\n[ Owner ]: " + aPlayers[mOwner]->GetName() + "\n[ Tenant ]: " + aPlayers[position]->GetName() + "[ Amount ]: " + char(156) + to_string(*pDieRoll));
	//pay money
	aPlayers[position]->TakeMoney(*pDieRoll, cGame);
	aPlayers[mOwner]->TakeMoney(*pDieRoll, cGame);

	
}

istream& operator >> (istream& inputStream, CUtility& cUtility)
{
	inputStream >> cUtility.mPrice;
	return inputStream;
}