#include "CProperty.h"

CProperty::CProperty(istream& file) : CTile(file)
{
	file >> *this;
	mOwner = -1;
	mHouses = 0;
	mHotel = false;
	mMortgage = false;
}
CProperty::~CProperty()
{
}

int CProperty::GetOwner()
{
	return mOwner;
}

void CProperty::SetPrice(int tPrice)
{
	mPrice = tPrice;
}

int CProperty::GetPrice()
{
	return mPrice;
}

void CProperty::SetRent(int& tRent)
{
	mRent = tRent;
}

int CProperty::GetRent()
{
	return mRent;
}

void CProperty::UpdateRent()
{
	
	if (!mHotel)
	{
		switch (mHouses)
		{
		case 0:
			mRent = mORent;
			break;
		case 1:
			mRent = mORent * 5;
			break;
		case 2:
			mRent = mORent * 15;
			break;
		case 3:
			mRent = mORent * 45;
			break;
		case 4:
			mRent = mORent * 80;
			break;
		default:
			mRent = mORent;
			break;
		}
	}
	else //if there is a hotel
	{
		mRent = mORent * 125;
	}
}

void CProperty::SetHouses(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position, unique_ptr<Logger>& ioLog)
{
	//if no hotel and less houses than max
	if (mHotel != 1 && mHouses < 4)
	{
		unique_ptr<int> pHousePrice = make_unique<int>();
		*pHousePrice = mPrice * 0.2;

		if (aPlayers[position]->GetMoney() >= *pHousePrice) //if player has enough to purchase
		{
			aPlayers[position]->TakeMoney(*pHousePrice, cGame);
			mHouses++;
			UpdateRent();
			ioLog->writeToFile("[ House Added ]: " + mName + "\n");
		}
		else { //if player doesn't have enough money
			ioLog->writeToFile(aPlayers[position]->GetName() + " does not have enough money to add to their property\n");
		}
	}
	else //if Hotel is 1, houses is equal to 4
	{
		SetHotels(aPlayers, cGame, position, ioLog); //pass it to hotels
	}
}

void CProperty::SetHotels(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position, unique_ptr<Logger>& ioLog)
{
	if (mHouses == 4 && mHotel == 0) //if max houses and no hotel
	{
		//calculate price of hotel
		unique_ptr<int> pHotelPrice = make_unique<int>();

		*pHotelPrice = mPrice * 0.5;

		//if player has enough
		if (aPlayers[position]->GetMoney() >= *pHotelPrice) //if player has enough to purchase
		{
			aPlayers[position]->TakeMoney(*pHotelPrice, cGame);
			ioLog->writeToFile("[ Hotel added ]: " + mName);
			mHotel = true;
			UpdateRent();
		}
		else
		{
			ioLog->writeToFile("[ Insufficient Funds ]: Cannot add building");
		}

	}
	else if (mHotel == 1) //if hotel
	{
		ioLog->writeToFile("[ Already Exists]: Building cannot be added");
	}
	else //hotel already added 
	{
		ioLog->writeToFile("[ Already Exists]: Building cannot be added");
	}
}

void CProperty::ResetTile()
{
	mOwner = -1;
	mHouses = 0;
	mHotel = false;
	mMortgage = false;
	mRent = mORent;

}

void CProperty::BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog)
{
	//property bought
	ioLog->writeToFile("\n[ Property Bought ] \n[ Name ]: " + mName + "\n[ Price ]: " + char(156) + to_string(mPrice) + "\n[ Colour ]: " + mGroup + "\n");

	mOwner = position;

	//player pays money
	aPlayers[position]->TakeMoney(mPrice, cGame);
}

void CProperty::PayRent(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position, unique_ptr<Logger>& ioLog)
{
	//totalRent is equal to the rent set x a multipler
	unique_ptr<int> mTotalRent = make_unique<int>();
	*mTotalRent = mRent;


	//if not mortgaged
	if (mMortgage == false)
	{

		aPlayers[position]->TakeMoney(*mTotalRent, cGame);
		aPlayers[mOwner]->GiveMoney(*mTotalRent, cGame);
	}
	//if mortgaged
	else
	{
		aPlayers[position]->TakeMoney(*mTotalRent, cGame);
	}


	//ioLog->writeToFile(aPlayers[position]->GetName() + " paid " + char(156) + to_string(*mTotalRent) + " to " + aPlayers[mOwner]->GetName() + "\n");
	ioLog->writeToFile("\n[ Rent ] \n[ Landlord ]: " + aPlayers[mOwner]->GetName() + "\n[ Tenant ]: " + aPlayers[position]->GetName() + "\n[ Amount ]: " + char(156) + to_string(*mTotalRent) + "\n");
}


string CProperty::GetGroup()
{
	return mGroup;
}

//mortgages property
void CProperty::MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position)
{
		mMortgage = true;
		aPlayers[position]->GiveMoney(mPrice / 2, cGame);
}

void CProperty::PayMortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog)
{
	//unmortgage the property
	mMortgage = false;
	aPlayers[position]->TakeMoney(mPrice * 1.1, cGame);
	ioLog->writeToFile("[ Mortgage Paid ]");
}

istream& operator>>(istream& inputStream, CProperty& cProperty)
{
    inputStream >> cProperty.mPrice >> cProperty.mRent;
	cProperty.mORent = cProperty.mRent;

    //input text here
	bool nextWord = false;

	int nextChar = 0;

	//loop to check the words if there are any more
	do {
		//locally defined string
		string sWord;
		//input a word into the string
		inputStream >> sWord;

		//appends sName (square name) with it
		cProperty.mGroup += sWord;

		inputStream >> ws;
		//peeks at the next character
		nextChar = inputStream.peek();

		//is true if not at end of file
		//AND next digit is not an int
		nextWord = !isdigit(nextChar) && nextChar != EOF;

		if (nextWord)
		{
			cProperty.mGroup += " ";
		}


	} while (nextWord);
    return inputStream;
}
