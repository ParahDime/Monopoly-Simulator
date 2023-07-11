#pragma once
#include "CCard.h"
class CCardLose :
    public CCard
{
private:
    int mMoney;
public:
    CCardLose(istream& file);
    ~CCardLose();

    void SetMoney(int tMoney);
    int GetMoney();

    void GetText();

    friend istream& operator >> (istream& inputStream, CCardLose& cCardLose);
};

