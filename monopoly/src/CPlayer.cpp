#include "CPlayer.h"
#include "CGame.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::SetName(string name)
{
	mName = name;
}

bool CPlayer::HasProperties() //check if any properties
{
	if (!ownedTiles.empty())
	{
		return true;
	}
	return false;
}

//get a specific property
int CPlayer::GetProperty() //get last property in the vector
{
	return ownedTiles.back();
}

void CPlayer::AddProperty() //add property to vector
{
	ownedTiles.push_back(mPosition);
}

void CPlayer::RemoveProperty() //remove last property in vector
{
	ownedTiles.pop_back();
}

void CPlayer::GetParkingMoney(int money) {
	mMoney += money;
}

void CPlayer::GiveMoney(int money, unique_ptr<CGame>& cGame)
{
	mMoney += money;

	cGame->BankTotalLose(money);
}

void CPlayer::TakeMoney(int money, unique_ptr<CGame>& cGame)
{
	mMoney -= money;
	cGame->BankTotalGain(money);
}

void CPlayer::SetBankrupt()
{
	mIsBankrupt = true;
}

void CPlayer::changeJailCard()
{
	if (mJailCard == true)
	{
		mJailCard = false;
	}
	else
	{
		mJailCard = true;
	}
}

//moves the player forward
void CPlayer::MovePosition(int num)
{
	mPosition += num;
}

void CPlayer::SetPosition(int position)
{
	mPosition = position;
}

void CPlayer::BoardLap(int boardSize)
{
	mPosition -= boardSize;
}

void CPlayer::SetJailCounter(int counter)
{
	mJailCounter = counter;
}

void CPlayer::PassTurn()
{
	if (mJailCounter > 0)
	{
		mJailCounter--;
	}
}

void CPlayer::SetPersonality(unique_ptr<IBoneBrain> newBrain)
{

}

bool CPlayer::DecidesToBuy(int propertyCost)
{
	return true;
}

void CPlayer::SetValues(unique_ptr<CGame>& cGame)
{
	mMoney = cGame->GetPlayerMoney();
	mPosition = 0;
	mJailCounter = 0;
	mJailCard = false;

	cGame->BankTotalLose(mMoney);
}
