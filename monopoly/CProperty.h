#pragma once
#include "CTile.h"
#include "CPlayer.h"
#include "CGame.h"
class CProperty :
    public CTile
{
private:
    int mOwner;
    int mPrice;
    int mRent;
    int mORent; //original rent
    int mHouses;
    bool mHotel;
    string mGroup;
    bool mMortgage;
public:
    CProperty(istream& file);
    ~CProperty();

    int GetOwner();

    void SetPrice(int tPrice);
    int GetPrice();

    void SetRent(int& tRent);
    int GetRent();
    void UpdateRent();

    int GetHouses();
    void SetHouses(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position);
    int GetHotels();
    void SetHotels(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position);

    void ResetTile();

    void BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
    void PayRent(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position);
    string GetGroup();
    friend istream& operator >> (istream& inputStream, CProperty& cProperty);
    bool isMortgaged();
    void MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
    void PayMortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
};

