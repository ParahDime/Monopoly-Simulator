#include "Header.h"
#pragma once
class CGame
{
private:
	int mBank; //value of 40k
	int mGoMoney = 200; //to be set by the tile
	int mCurrentRound;
	int mMaxRound;
	int mPlayers; //no of players
	int mLow; //low roll
	int mHigh; //high roll
	int mDiceNo; //number of dice rolled
	int mMultiplier; //difficulty used, higher the number, more difficult

	int mMaxTiles; //the maximum amount of tiles that are on the board that can be bought
	int mTileOwned; //the amount of tiles owned by players
public:
	CGame();
	~CGame();
	void SetValues();

	int GetCurrentRound();
	int GetMaxRound();
	void SetMaxRound(int round);

	void NextRound();

	void MaxTileCount();

	string GetDifficulty();
	void SetDifficulty(int multiplier);

	int GetPlayers();
	void SetPlayers(int players);

	int GetLowRoll();
	int GetHighRoll();

	int GetDiceNo();
	void SetDiceNo(int diceNo);

	void BankTotalLose(int money);
	void BankTotalGain(int money);

	int GetGoMoney(int i);
	int GetGoMoney();

	int GetMultiplier(); //requires 
};

