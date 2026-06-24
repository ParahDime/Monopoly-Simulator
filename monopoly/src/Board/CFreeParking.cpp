#include "CFreeParking.h"
#include "CTile.h"

CFreeParking::CFreeParking(istream& file) :  CTile(file)
{
}

CFreeParking::~CFreeParking()
{
}

void CFreeParking::OutputText(vector<CPlayer*>& aPlayers, int position, unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile(aPlayers[position]->GetName() + "is resting.\n");
}
