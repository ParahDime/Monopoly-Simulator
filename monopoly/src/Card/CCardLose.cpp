#include "CCardLose.h"

CCardLose::CCardLose(istream& file) : CCard(file)
{
	file >> *this;
}

CCardLose::~CCardLose()
{
}



void CCardLose::SetMoney(int tMoney)
{
	mMoney = tMoney;
}

int CCardLose::GetMoney()
{
	return mMoney;
}

void CCardLose::GetText(unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile(mName + " " + to_string(mMoney) + "\n");
}


istream& operator>>(istream& inputStream, CCardLose& cCardLose)
{
	inputStream >> cCardLose.mMoney;
	return inputStream;
}
