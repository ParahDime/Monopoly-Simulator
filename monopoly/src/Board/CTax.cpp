#include "CTax.h"

CTax::CTax(istream& file) : CTile(file)
{
	file >> *this;

}

CTax::~CTax()
{

}

void CTax::PayTax(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position, unique_ptr<Logger>& ioLog)
{
	unique_ptr<string> Tax = make_unique<string>("\n[ Tax ] \n[ Amount ]: ");
	ioLog->writeToFile(*Tax + char(156) + to_string(mPrice));
	//lose money
	aPlayers[position]->TakeMoney(mPrice, cGame);
	//bank gains money
	cGame->BankTotalGain(mPrice);

}

int CTax::GetTax()
{
	return mPrice;
}

istream& operator >> (istream& inputStream, CTax& tax)
{
	inputStream >> tax.mPrice;
	return inputStream;
}
