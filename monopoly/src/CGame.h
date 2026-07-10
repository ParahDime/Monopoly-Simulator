#include "Header.h"
#pragma once
class CGame
{
private:
	int mBank; //value of 40k
	int mGoMoney; //to be set by the tile
	int mCurrentRound;
	int mMaxRound;
	int mPlayers; //no of players
	int mHigh; //high roll
	int mDiceNo; //number of dice rolled
	int mMultiplier; //difficulty used, higher the number, more difficult

	int mMaxTiles; //the maximum amount of tiles that are on the board that can be bought
	int mTileOwned; //the amount of tiles owned by players
	bool mParking = false; //bool if money is given on free parking
	int mParkingAmount = 0;

	bool mPlaying = false; // determines if player1 is playing
	bool mHouseRules = false;

public:
	CGame();
	~CGame();

	int GetCurrentRound();
	int GetMaxRound();
	void SetMaxRound(int round);

	void NextRound();

	void MaxTileCount();

	string GetDifficulty();
	void SetDifficulty(int multiplier);

	int GetPlayers();
	void SetPlayers(int players);
	int GetPlayerMoney();

	int GetLowRoll();
	int GetHighRoll();
	void SetHighRoll(int diceFace);

	int GetDiceNo();
	void SetDiceNo(int diceNo);

	int rollDice(); //roll the dice, return number

	void SetBank(int money);
	void BankTotalLose(int money);
	void BankTotalGain(int money);

	void SetGoMoney(int i);
	int GetGoMoney();

	int GetMultiplier(); //requires 

	bool isPlaying();
	void setPlaying(bool playing);

	void SetParkingRule(bool parking);
	bool GetParkingRule();

	int GetParkingMoney();
	void SetParkingMoney(int money);
	void ResetParking();

	bool GetHouseRules();
	void SetHouseRules();
	
};

