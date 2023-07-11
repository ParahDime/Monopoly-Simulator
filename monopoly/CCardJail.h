#pragma once
#include "CCard.h"
class CCardJail :
    public CCard
{
private:

public:
    CCardJail(istream& file);
    ~CCardJail();

    void GetText();
};

