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

void CUtility::BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position)
{
	cout << aPlayers[position]->GetName() << " buys " << mName << " for " << char(156) << mPrice << "\n";

	mOwner = position;

	//player pays money
	aPlayers[position]->TakeMoney(mPrice, cGame);
	//bank gains money
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

void CUtility::PayBill(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pDieRoll, unique_ptr<int>& pTypeOwned)
{
	//take the value of the role
	*pDieRoll = (*pDieRoll * *pTypeOwned) * 4;

	//difficulty multiplier
	if (position == 0)
	{
		*pDieRoll *= cGame->GetMultiplier();
	}

	cout << aPlayers[position]->GetName() << " pays " << char(156) << *pDieRoll << " to " << aPlayers[mOwner]->GetName() << "\n";
	//pay money
	aPlayers[position]->TakeMoney(*pDieRoll, cGame);
	aPlayers[mOwner]->TakeMoney(*pDieRoll, cGame);

	
}

istream& operator >> (istream& inputStream, CUtility& cUtility)
{
	inputStream >> cUtility.mPrice;
	return inputStream;
}