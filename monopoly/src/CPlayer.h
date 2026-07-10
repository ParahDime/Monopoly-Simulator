#include "Header.h"
#include "CGame.h"
#include "Personality.h"

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
	unique_ptr<IBoneBrain> m_brain; //struct to manage decision making

public:
	CPlayer();
	~CPlayer();

	void SetName(string name);
	string GetName();

	void GetParkingMoney(int money);
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

	void SetPersonality(unique_ptr<IBoneBrain> newBrain);
	bool DecidesToBuy(int propertyCost);

	void SetValues(unique_ptr<CGame>& cGame);
};

