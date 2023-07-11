#include "CJail.h"

CJail::CJail(istream& file) : CTile(file)
{

}

CJail::~CJail()
{

}

void CJail::PassingJail(vector<CPlayer*>& aPlayers, int position)
{
	//use if statement to check if player is in prison

	//else

	cout << aPlayers[position]->GetName() << " is just passing through\n";
}
