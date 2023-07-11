
#include "CTile.h"
#include "Header.h"
#include "CPlayer.h"
#pragma once

class CJail :
    public CTile
{
protected:

public:
    CJail(istream& file);
    ~CJail();

    void PassingJail();
    void InJail();

    void PassingJail(vector<CPlayer*>& aPlayers, int position);
    
};

