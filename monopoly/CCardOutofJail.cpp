#include "CCardOutofJail.h"

CCardOutofJail::CCardOutofJail(istream& file) : CCard(file)
{
	file >> *this;
}

CCardOutofJail::~CCardOutofJail()
{
}

void CCardOutofJail::GetText()
{
	cout << mName << "\n";
}
