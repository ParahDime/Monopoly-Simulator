#pragma once
#include "CTile.h"
#include "Header.h"
#include "CPlayer.h"

class CGoToJail :
    public CTile
{
protected:

public:
    CGoToJail(istream& file);
    ~CGoToJail();

    void GoToJail(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position); //sends the player to the jail tile
};

