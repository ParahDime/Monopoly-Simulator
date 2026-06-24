#include "CCardEarn.h"

CCardEarn::CCardEarn(istream& file) : CCard(file)
{
	file >> *this;
}

CCardEarn::~CCardEarn()
{
}

void CCardEarn::GetText(unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile(mName + " " + to_string(mMoney) + "\n");
}

void CCardEarn::SetMoney(int tMoney)
{
	mMoney = tMoney;
}

int CCardEarn::GetMoney()
{
	return mMoney;
}


istream& operator>>(istream& inputStream, CCardEarn& cCardEarn)
{
	inputStream >> cCardEarn.mMoney;
	return inputStream;
}
