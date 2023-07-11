#pragma once
#include "CCard.h"
#include "CGame.h"
#include "CPlayer.h"

class CCardOutofJail :
    public CCard
{
private:

public:
    CCardOutofJail(istream& file);
    ~CCardOutofJail();

    void GetText();
};

