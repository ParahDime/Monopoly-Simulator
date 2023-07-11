#include "CTile.h"



CTile::CTile(istream& file)
{
	//file >> mType;
	file >> *this;
}

CTile::~CTile()
{
}

string CTile::GetName()
{
	return mName;
}

int CTile::GetType()
{
	return mType;
}

void CTile::SetType(int type)
{
	mType = type;
}

void CTile::ResetTile()
{
}

void CTile::OutputText(vector<CPlayer*>& aPlayers, int position)
{
	//cout << "Player has landed on a tile. Do nothing for one turn\n";
}

void CTile::PayTax(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position)
{
}

void PayRent(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position)
{

}

void CTile::BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position)
{
	//cout << "Tile cannot be bought\n";
}

void CTile::PayBill(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pDieRoll, unique_ptr<int>& pTypeOwned)
{
}

void CTile::PayRent(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position)
{
}

void CTile::PayFare(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pTypeOwned)
{
}


int CTile::GetOwner()
{
	//cout << "Tile has no owner\n";
	return int();
}

string CTile::GetGroup()
{
	//is not part of a group, return a void value
	return string();
}

void CTile::SetPrice(int tPrice)
{
}

int CTile::GetPrice()
{
	return int();
}

int CTile::GetHouses()
{
	return 0;
}

int CTile::GetRent()
{
	return int();
}

void CTile::SetRent(int& tRent)
{
}

void CTile::SetHouses(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position)
{
}

int CTile::GetHotels()
{
	return 0;
}

void CTile::SetHotels(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position)
{
}

void CTile::UpdateRent()
{
}

bool CTile::IsMortgaged()
{
	return bool();
}

void CTile::MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position)
{
}

void CTile::PayMortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position)
{
}

void CTile::PassingJail(vector<CPlayer*>& aPlayers, int position)
{
}

void CTile::GoToJail(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position)
{
}


//operator overrider for putting in names
istream& operator>>(istream& inputStream, CTile& aBoard)
{
	bool nextWord = false;

	int nextChar = 0;

	//loop to check the words if there are any more
	do {
		//locally defined string
		string sWord;
		//input a word into the string
		inputStream >> sWord;

		//appends sName (square name) with it
		aBoard.mName += sWord;

		inputStream >> ws;
		//peeks at the next character
		nextChar = inputStream.peek();

		//is true if not at end of file
		//AND next digit is not an int
		nextWord = !isdigit(nextChar) && nextChar != EOF;

		if (nextWord)
		{
			aBoard.mName += " ";
		}


	} while (nextWord);

	return inputStream;

}

ostream& operator<<(ostream& outputStream, CTile& pBoard)
{

	outputStream << pBoard.mName;
	return outputStream;

}

