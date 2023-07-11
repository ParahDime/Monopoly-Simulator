#include "CCardJail.h"

CCardJail::CCardJail(istream& file) : CCard(file)
{
	file >> *this;
}

CCardJail::~CCardJail()
{
}

void CCardJail::GetText()
{
	cout << mName << "\n";
}
