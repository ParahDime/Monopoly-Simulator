#pragma once
#include "Header.h"
#include "CTile.h"
#include "CPlayer.h"
class CChance :
    public CTile
{
protected:
    //all cards will have a number (denoting their type) and name
public:
    //initialiser
    CChance(istream& file);
    ~CChance();
};

