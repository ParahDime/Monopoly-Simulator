#include "CCardOutofJail.h"

CCardOutofJail::CCardOutofJail(istream& file) : CCard(file)
{
	file >> *this;
}

CCardOutofJail::~CCardOutofJail()
{
}

void CCardOutofJail::GetText(unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile(mName + "\n");
}
