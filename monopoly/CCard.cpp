#include "CCard.h"

CCard::CCard(istream& file)
{
	file >> *this;
}

CCard::~CCard()
{

}

void CCard::SetType(int tType)
{
	mType = tType;
}

int CCard::GetType()
{
	return mType;
}

void CCard::SetText(string tText)
{
	mName = tText;
}

void CCard::GetText()
{
	cout << mName;
}

void CCard::SetMoney()
{
}

int CCard::GetMoney()
{
	return int();
}

void CCard::SetSpecific()
{
}

bool CCard::GetSpecific()
{
	return bool();
}

void CCard::SetNaming()
{
}

string CCard::GetNaming()
{
	return string();
}

void CCard::SetTyping()
{
}

int CCard::GetTyping()
{
	return 0;
}

void CCard::SetHouseCost(int& tHouse)
{
}

int CCard::GetHouseCost()
{
	return 0;
}

int CCard::GetHotelCost()
{
	return int();
}

void CCard::SetHotelCost(int& tHouse)
{
}

//operator overrider for putting in names

//TODO: edit to work properly
istream& operator>>(istream& inputStream, CCard& aCard)
{
	bool nextWord = false;

	int nextChar = 0;

	//loop to check the words if there are any more
	do {
		//locally defined string
		string sWord;
		//input a word into the string
		
		nextChar = inputStream.peek();

		if (isdigit(nextChar))
		{
			break;
		}
		else {
			inputStream >> sWord;
			inputStream >> ws;
			aCard.mName += sWord + " ";
		}

		nextWord = !isdigit(nextChar) && nextChar != EOF;

	} while (nextWord);

	return inputStream;

}

ostream& operator<<(ostream& outputStream, CCard& pCard)
{

	outputStream << pCard.mName;
	return outputStream;

}