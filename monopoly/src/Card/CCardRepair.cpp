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

void CCardRepair::GetText(unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile(mName + " Pay " + to_string(mHouseRepair) + " for each house and " + to_string(mHotelRepair) + " for each hotel.\n");
}

istream& operator>>(istream& inputStream, CCardRepair& cCardRepair)
{
	inputStream >> cCardRepair.mHouseRepair >> cCardRepair.mHotelRepair;
	return inputStream;
}
