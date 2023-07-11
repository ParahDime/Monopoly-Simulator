#pragma once
#include "CCard.h"
#include "Header.h"
#include "CPlayer.h"
class CCardEarn :
    public CCard
{
private:
    int mMoney;
public:
    CCardEarn(istream& file);
    ~CCardEarn();

    void GetText();

    void SetMoney(int tMoney);
    int GetMoney();
    friend istream& operator >> (istream& inputStream, CCardEarn& cCardEarn);
};

