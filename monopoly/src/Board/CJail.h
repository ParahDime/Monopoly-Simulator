
#include "CTile.h"
#include "../Header.h"
#include "../CPlayer.h"
#include "../Logger.h"
#pragma once

class CJail :
    public CTile
{
protected:

public:
    CJail(istream& file);
    ~CJail();

    void InJail();
    void PassingJail(vector<CPlayer*>& aPlayers, int position, unique_ptr<Logger>& ioLog);
    
};

