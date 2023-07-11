#include "Header.h"
#include "CGame.h"
#include "CPlayer.h"

#pragma once
class CCard
{
protected:
	int mType;
	string mName;
public:
	CCard(istream& file);
	~CCard();

	void SetType(int tType);
	int GetType();

	void SetText(string tText);
	virtual void GetText();

	virtual void SetMoney();
	virtual int GetMoney();

	virtual void SetSpecific();
	virtual bool GetSpecific();
	virtual void SetNaming();
	virtual string GetNaming();
	virtual void SetTyping();
	virtual int GetTyping();

	virtual void SetHouseCost(int& tHouse);
	virtual int GetHouseCost();
	virtual void SetHotelCost(int& tHouse);
	virtual int GetHotelCost();


	friend istream& operator >> (istream& inputStream, CCard& aBoard);
	friend ostream& operator << (ostream& outputStream, CCard& aBoard);
};

