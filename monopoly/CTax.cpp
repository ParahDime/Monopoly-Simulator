#include "CTax.h"

CTax::CTax(istream& file) : CTile(file)
{
	file >> *this;

}

CTax::~CTax()
{

}

void CTax::PayTax(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position)
{
	cout << aPlayers[position]->GetName() << " pays " << char(156) << mPrice << " in tax.\n";
	//lose money
	aPlayers[position]->TakeMoney(mPrice, cGame);
	//bank gains money
	cGame->BankTotalGain(mPrice);

}

istream& operator >> (istream& inputStream, CTax& tax)
{
	inputStream >> tax.mPrice;
	return inputStream;
}
