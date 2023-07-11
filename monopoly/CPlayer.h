#include "Header.h"
#include "CGame.h"

#pragma once
class CPlayer
{
private:
	string mName;
	int mMoney;
	int mPosition;
	int mJailCounter = 0;
	bool mJailCard = false;
	bool mIsBankrupt = false;

public:
	CPlayer();
	~CPlayer();

	void SetName(string name);
	string GetName();

	int GetMoney();
	void GiveMoney(int money, unique_ptr<CGame>& cGame);
	void TakeMoney(int money, unique_ptr<CGame>& cGame);

	void SetBankrupt();
	bool IsBankrupt();

	void changeJailCard();
	bool getJailCard();

	void MovePosition(int num);
	int GetPosition();
	void SetPosition(int position);
	void BoardLap(int boardSize);

	void SetJailCounter(int counter);
	int GetJailCounter();
	void PassTurn();

	void SetValues(unique_ptr<CGame>& cGame);
};

