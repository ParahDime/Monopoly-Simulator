#pragma once
#include "CTile.h"
#include "Header.h"
#include "CPlayer.h"
class CFreeParking :
    public CTile
{
protected:

public:
    CFreeParking(istream& file);
    ~CFreeParking();

    void OutputText(vector<CPlayer*>& aPlayers, int position);

};

