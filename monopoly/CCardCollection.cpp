#include "CCardCollection.h"



CCardCollection::CCardCollection(istream& file) : CCard(file)
{
	file >> *this;
}

CCardCollection::~CCardCollection()
{
}

void CCardCollection::GetText()
{
	cout << mName << " " << mAmount;
}

istream& operator>>(istream& inputStream, CCardCollection& cCardCollection)
{
	inputStream >> cCardCollection.mAmount;
	return inputStream;
}