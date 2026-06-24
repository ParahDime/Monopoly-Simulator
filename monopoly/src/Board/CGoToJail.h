#pragma once
#include "CTile.h"
#include "../Header.h"
#include "../CPlayer.h"
#include "../Logger.h"

class CGoToJail :
    public CTile
{
protected:

public:
    CGoToJail(istream& file);
    ~CGoToJail();

    void GoToJail(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int& position, unique_ptr<Logger>& ioLog); //sends the player to the jail tile
};

