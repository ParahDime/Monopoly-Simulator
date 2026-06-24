#include "CCardCollection.h"



CCardCollection::CCardCollection(istream& file) : CCard(file)
{
	file >> *this;
}

CCardCollection::~CCardCollection()
{
}

void CCardCollection::GetText(unique_ptr<Logger>& ioLog)
{
	 ioLog->writeToFile(mName + " " + to_string(mAmount));
}

istream& operator>>(istream& inputStream, CCardCollection& cCardCollection)
{
	inputStream >> cCardCollection.mAmount;
	return inputStream;
}