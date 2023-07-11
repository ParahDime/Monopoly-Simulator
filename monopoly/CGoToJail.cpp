#include "CGoToJail.h"
#include "CTile.h"

CGoToJail::CGoToJail(istream& file) : CTile(file)
{
}

CGoToJail::~CGoToJail()
{
}

void CGoToJail::GoToJail(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position)
{

	cout << aPlayers[position]->GetName() << " is sent to jail.\n";

	for (int i = 0; i != aBoard.size(); i++)
	{
		if (aBoard[i]->GetType() == 5)
		{
			//moves player to jail
			aPlayers[position]->SetPosition(i);
		}
	}

	if (aPlayers[position]->getJailCard() == false)
	{
		//set player's "prison counter" to 3
		aPlayers[position]->SetJailCounter(3);
	}
	else
	{
		//sets the players get out of jail status to false (card is used)
		aPlayers[position]->changeJailCard();
		cout << aPlayers[position]->GetName() << "uses their get out of jail card\n";
		cout << aPlayers[position]->GetName() << "leaves jail\n";
		
	}
}
