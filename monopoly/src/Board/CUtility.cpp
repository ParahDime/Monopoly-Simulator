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

void CUtility::MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog, vector<CTile*>& aBoard)
{
	if (mMortgage == false)
	{
		mMortgage = true;
		int mortgageGain = (mPrice * 0.5) / 1.0;
		aPlayers[position]->GiveMoney(mortgageGain, cGame);
		ioLog->writeToFile("[ Mortgaged ]: " + mName + " for " + to_string(mortgageGain) + "\n");
		//get half money from property
	}
	else
	{
		cout << "[ Already mortgaged ]: " + mName + "\n";
	}	
}

void CUtility::PayMortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog)
{
	//unmortgage the property
	mMortgage = false;
	aPlayers[position]->TakeMoney(mPrice * 1.1, cGame);
	ioLog->writeToFile("[ Mortgage Paid ]");
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