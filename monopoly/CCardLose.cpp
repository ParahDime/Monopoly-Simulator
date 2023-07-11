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

void CCardLose::GetText()
{
	cout << mName << " " << mMoney << "\n";
}


istream& operator>>(istream& inputStream, CCardLose& cCardLose)
{
	inputStream >> cCardLose.mMoney;
	return inputStream;
}
