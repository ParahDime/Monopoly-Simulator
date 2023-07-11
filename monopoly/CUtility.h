#pragma once
#include "CTile.h"
#include "Header.h"
#include "CPlayer.h"
#pragma once

class CUtility :
    public CTile
{
protected:
    int mOwner;
    int mPrice;
    bool mMortgage;
public:
    CUtility(istream& file);
    ~CUtility();

    void ResetTile();
    int GetOwner();
    void BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
    void MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);

    void PayBill(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pDieRoll, unique_ptr<int>& pTypeOwned);

    friend istream& operator >> (istream& inputStream, CUtility& cUtility);
};

