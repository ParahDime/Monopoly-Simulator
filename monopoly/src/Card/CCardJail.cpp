#include "CCardJail.h"

CCardJail::CCardJail(istream& file) : CCard(file)
{
	file >> *this;
}

CCardJail::~CCardJail()
{
}

void CCardJail::GetText(unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile(mName + "\n");
}
