#pragma once
#include "CCard.h"
class CCardCollection :
    public CCard
{
private:
    int mAmount;
public:
    CCardCollection(istream& file);
    ~CCardCollection();

    void GetText(unique_ptr<Logger>& ioLog);

    friend istream& operator >>(istream& inputStream, CCardCollection& cCardCollection);
};

