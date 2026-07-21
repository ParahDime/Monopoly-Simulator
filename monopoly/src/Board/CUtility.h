#pragma once
#include "CTile.h"
#include "../Header.h"
#include "../CPlayer.h"
#pragma once

class CUtility :
    public CTile
{
protected:
    bool mOwnable = true;
    int mOwner;
    int mPrice;
    bool mMortgage = false;
public:
    CUtility(istream& file);
    ~CUtility();

    bool IsOwnable() const override { return true; }

    void ResetTile();
    int GetOwner();
    void BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog);
    void MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
    bool IsMortgaged() const { return mMortgage; };

    void PayBill(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pDieRoll, unique_ptr<int>& pTypeOwned, unique_ptr<Logger>& ioLog);

    friend istream& operator >> (istream& inputStream, CUtility& cUtility);
};

