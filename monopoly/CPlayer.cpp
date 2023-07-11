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

string CPlayer::GetName()
{
	return mName;
}

int CPlayer::GetMoney()
{
	return mMoney;
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

bool CPlayer::IsBankrupt()
{
	return mIsBankrupt;
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

bool CPlayer::getJailCard()
{
	return mJailCard;
}

//moves the player forward
void CPlayer::MovePosition(int num)
{
	mPosition += num;
}

int CPlayer::GetPosition()
{
	return mPosition;
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

int CPlayer::GetJailCounter()
{
	return mJailCounter;
}

void CPlayer::PassTurn()
{
	if (mJailCounter > 0)
	{
		mJailCounter--;
	}
}

void CPlayer::SetValues(unique_ptr<CGame>& cGame)
{
	mMoney = 1500;
	mPosition = 0;
	mJailCounter = 0;
	mJailCard = false;

	cGame->BankTotalLose(mMoney);
}
