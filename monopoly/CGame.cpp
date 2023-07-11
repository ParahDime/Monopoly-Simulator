#include "CGame.h"

CGame::CGame()
{
    mBank = 40000;
    mLow = 1;
    mHigh = 6;
    mCurrentRound = 1;
    mTileOwned = 0;
}



CGame::~CGame()
{
}

//if not customising the game
void CGame::SetValues()
{
    mMaxRound = 50;
    mPlayers = 4; //no of players
    mDiceNo = 1;
    mMultiplier = 2; //difficulty used
}

int CGame::GetMaxRound()
{
    return mMaxRound;
}

int CGame::GetCurrentRound()
{
    return mCurrentRound;
}

void CGame::SetMaxRound(int round)
{
    mMaxRound = round;
}

void CGame::SetDifficulty(int multiplier)
{
    mMultiplier = multiplier;


    //depending on value, mBank can be higher or lower
    if (mMultiplier >= 3) //if hard mode
    {
        mBank = 30000;
    }
    else if (mMultiplier == 1) //if easy mode
    {
        mBank = 50000;
    }
}

string CGame::GetDifficulty()
{
    switch (mMultiplier)
    {
    case 1:
        return "easy";
        break;
    case 2:
        return "normal";
        break;
    case 3:
        return "hard";
        break;
    }
}

void CGame::NextRound()
{
    mCurrentRound++;
}

void CGame::SetPlayers(int players)
{
    mPlayers = players;
}

int CGame::GetPlayers()
{
    return mPlayers;
}

void CGame::SetDiceNo(int diceNo)
{
    mDiceNo = diceNo;
}

int CGame::GetDiceNo()
{
    return mDiceNo;
}

void CGame::MaxTileCount()
{
    mMaxTiles++;
}

int CGame::GetLowRoll()
{
    return mLow;
}

int CGame::GetHighRoll()
{
    return mHigh;
}

void CGame::BankTotalGain(int money)
{
    mBank += money;
}

void CGame::BankTotalLose(int money)
{
    mBank -= money;
}

int CGame::GetGoMoney(int i)
{
    int GoMoney;
    switch (mMultiplier)
    {
    case 1:
        GoMoney = mGoMoney * 1.2;
        break;
    case 2:
        GoMoney = mGoMoney;
        break;
    case 3:
        GoMoney = mGoMoney * 0.8;
        break;
    default:
        GoMoney = mGoMoney;
        break;
    }

    return GoMoney;
}

int CGame::GetGoMoney()
{
    return mGoMoney;
}

int CGame::GetMultiplier()
{
    switch (mMultiplier)
    {
    case 1:
        return 0.8;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 1.2;
        break;
    default:
        break;
    }
    return 0;
}
