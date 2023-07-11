#pragma once
#include "CCard.h"
class CCardRepair :
    public CCard
{
private:
    int mHouseRepair;
    int mHotelRepair;
public:
    CCardRepair(istream& file);
    ~CCardRepair();

    void SetHouseCost(int& tHouse);
    int GetHouseCost();
    void SetHotelCost(int& tHotel);
    int GetHotelCost();
    void GetText();
    friend istream& operator >> (istream& inputStream, CCardRepair& cCardRepair);
};

