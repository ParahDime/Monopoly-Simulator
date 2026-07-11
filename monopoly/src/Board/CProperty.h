#pragma once
#include "CTile.h"
#include "../CPlayer.h"
#include "../CGame.h"
#include "../Logger.h"
class CProperty :
    public CTile
{
private:
    bool mOwnable = true;
    int mOwner;
    int mPrice = 0;
    int mRent = 0;
    int mORent = 0; //original rent
    int mHouses;
    bool mHotel;
    string mGroup;
    bool mMortgage;
public:
    CProperty(istream& file);
    ~CProperty();

    bool IsOwnable() const override { return true; }

    int GetOwner();

    void SetPrice(int tPrice);
    int GetPrice();

    void SetRent(int& tRent);
    int GetRent();
    void UpdateRent();

    int GetHouses() const { return mHouses; };
    void SetHouses(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position, unique_ptr<Logger>& ioLog);
    int GetHotels() const { return mHotel; };
    void SetHotels(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position, unique_ptr<Logger>& ioLog);

    void ResetTile();

    void BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog);
    void PayRent(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position, unique_ptr<Logger>& ioLog);
    string GetGroup();
    friend istream& operator >> (istream& inputStream, CProperty& cProperty);
    bool isMortgaged() const { return mMortgage; };
    void MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
    void PayMortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog);
};

