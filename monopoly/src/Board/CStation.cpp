#include "CStation.h"

CStation::CStation(istream& file) : CTile(file)
{
	file >> *this;
	mOwner = -1;
	mMortgage = false;
}

CStation::~CStation()
{
}

void CStation::BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile("\n[ Station Bought ]: \n[ Name ]: " + mName + "\n[ Price ]: " + char(156) + to_string(mPrice) + "\n");

	mOwner = position;

	//player pays money
	aPlayers[position]->TakeMoney(mPrice, cGame);
}

void CStation::PayFare(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pTypeOwned, unique_ptr<Logger>& ioLog)
{
	//calculate total
	unique_ptr<int> mTotalRent = make_unique<int>();
	*mTotalRent = mRent * (2 * *pTypeOwned); //uses power of 2 to calculate amount of rent owned

	//difficulty multiplier
	if (position == 0)
	{
		*mTotalRent *= cGame->GetMultiplier();
	}

	ioLog->writeToFile("\n[ Rent ] \n[ Landlord ]: " + aPlayers[mOwner]->GetName() + "\n[ Tenant ]: " + aPlayers[position]->GetName() + "\n[ Amount ]: " + char(156) + to_string(*mTotalRent) + "\n");
	//pay money
	aPlayers[position]->TakeMoney(*mTotalRent, cGame);
	aPlayers[mOwner]->GiveMoney(*mTotalRent, cGame);
}

int CStation::GetOwner()
{
	return mOwner;
}

void CStation::ResetTile()
{
	mOwner = -1;
	mMortgage = false;
}

void CStation::MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position)
{
	if (mMortgage == false)
	{
		mMortgage = true;
		aPlayers[position]->GiveMoney(mPrice / 2, cGame);

		//get half money from property
	}
	else
	{
		mMortgage = false;
	}
}

istream& operator>>(istream& inputStream, CStation& cStation)
{
	// TODO: insert return statement here
	inputStream >> cStation.mPrice >> cStation.mRent;
	return inputStream;
}
