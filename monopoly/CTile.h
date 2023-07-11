#include "Header.h"
#include "CPlayer.h"
#pragma once

class CTile
{
protected:
	int mType = 0;
	string mName;
public:
	CTile(istream& file);
	~CTile();

	string GetName();

	int GetType();
	void SetType(int type);

	virtual void ResetTile();

	virtual void BuyProperty(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position); //property ( 1 2 3 
	virtual void PayBill(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pDieRoll, unique_ptr<int>& pTypeOwned);
	virtual void PayRent(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position);
	virtual void PayFare(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<int>& pTypeOwned);
	virtual int GetOwner();
	virtual string GetGroup();

	virtual void SetPrice(int tPrice);
	virtual int GetPrice();
	virtual int GetHouses();
	virtual int GetRent();
	virtual void SetRent(int& tRent);
	virtual void SetHouses(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position);
	virtual int GetHotels();
	virtual void SetHotels(vector<CPlayer*>& aPlayers, unique_ptr<CGame>& cGame, int& position);

	virtual void UpdateRent();
	virtual bool IsMortgaged();
	virtual void MortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
	virtual void PayMortgageTile(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int& position);
	virtual void PassingJail(vector<CPlayer*>& aPlayers, int position); //jail ( 5

	virtual void GoToJail(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position);

	virtual void OutputText(vector<CPlayer*>& aPlayers, int position); //free parking ( 9

	virtual void PayTax(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position);

	friend istream& operator >> (istream& inputStream, CTile& aBoard);
	friend ostream& operator << (ostream& outputStream, CTile& aBoard);
};

