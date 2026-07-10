#include "CFreeParking.h"
#include "CTile.h"

CFreeParking::CFreeParking(istream& file) :  CTile(file)
{
}

CFreeParking::~CFreeParking()
{
}

void CFreeParking::OutputText(vector<CPlayer*>& aPlayers, int position, unique_ptr<Logger>& ioLog, bool Collection)
{
	if (!Collection) {
		ioLog->writeToFile("[ Free Parking ]: " + aPlayers[position]->GetName() + " is resting.\n");
	}
	else {
		ioLog->writeToFile("[ Free Parking ] \nCollect fines \n[ Amount ]: "); //collect fines from tax, fines etc
	}
}
