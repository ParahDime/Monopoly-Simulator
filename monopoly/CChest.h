#pragma once
#include "CTile.h"
#include "CPlayer.h"
class CChest :
    public CTile
{
protected:

public:
    CChest(istream& file);
    ~CChest();
};

