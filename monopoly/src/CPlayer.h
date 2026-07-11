#include "Header.h"
#include "CGame.h"
#include "CPersonality.h"

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
	unique_ptr<IBoneBrain> mBrain; //struct to manage decision making

public:
	CPlayer();
	~CPlayer();

	void SetName(string name);
	string GetName() const { return mName; };

	void GetParkingMoney(int money);
	int GetMoney() const { return mMoney; };
	void GiveMoney(int money, unique_ptr<CGame>& cGame);
	void TakeMoney(int money, unique_ptr<CGame>& cGame);

	void SetBankrupt();
	bool IsBankrupt() const { return mIsBankrupt; };

	void changeJailCard();
	bool getJailCard() const { return mJailCard; };

	void MovePosition(int num);
	int GetPosition() const { return mPosition; };
	void SetPosition(int position);
	void BoardLap(int boardSize);

	void SetJailCounter(int counter);
	int GetJailCounter() const { return mJailCounter; };
	void PassTurn();

	void SetPersonality(unique_ptr<IBoneBrain> newBrain);
	bool DecidesToBuy(int propertyCost);

	void SetValues(unique_ptr<CGame>& cGame);

	//functions below point to CPersonality.h
	bool PassBuyPropertyDecision(int cost) const {
		return mBrain->ShouldBuyProperty(this, cost);
	}

	bool PassBuildHouseDecision(int cost) const {
		return mBrain->ShouldBuildHouse(this, cost);
	}

	int PassBidDecision(int propertyCost, int currentHighestBid) const {
		return mBrain->GetBidAmount(this, propertyCost, currentHighestBid);
	}
};

