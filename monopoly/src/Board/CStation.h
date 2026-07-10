#pragma once
#include "CTile.h"
#include "../Header.h"
#include "../CPlayer.h"

class CStation :
    public CTile
{
protected:
    bool mOwnable = true;
    int mOwner;
    int mPrice;
    int mRent;
    bool mMortgage;
public:
    CStation(istream& file);
    ~CStation();

    bool IsOwnable() const override { return true; }
    void BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog);
    void PayFare(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pTypeOwned, unique_ptr<Logger>& ioLog);
    void MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
    int GetOwner();

    void ResetTile();

    friend istream& operator >> (istream& inputStream, CStation& cStation);
};

