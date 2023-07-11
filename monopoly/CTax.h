#include "Header.h"
#include "CPlayer.h"
#pragma once
#include "CTile.h"
class CTax :
    public CTile
{
protected:
    int mPrice;
public:
    CTax(istream& file);
    ~CTax();

    void PayTax(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, int position);

    friend istream& operator >> (istream& inputStream, CTax& tax);
};

