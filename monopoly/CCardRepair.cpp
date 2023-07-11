#include "CCardRepair.h"

CCardRepair::CCardRepair(istream& file) : CCard(file)
{
	file >> *this;
}

CCardRepair::~CCardRepair()
{
}

void CCardRepair::SetHouseCost(int& tHouse)
{
	mHouseRepair = tHouse;
}

int CCardRepair::GetHouseCost()
{
	return mHouseRepair;
}

void CCardRepair::SetHotelCost(int& tHotel)
{
	mHotelRepair = tHotel;
}

int CCardRepair::GetHotelCost()
{
	return mHotelRepair;
}

void CCardRepair::GetText()
{
	cout << mName << " Pay " << mHouseRepair << " for each house and " << mHotelRepair << " for each hotel.\n";
}

istream& operator>>(istream& inputStream, CCardRepair& cCardRepair)
{
	inputStream >> cCardRepair.mHouseRepair >> cCardRepair.mHotelRepair;
	return inputStream;
}
