#pragma once
#include "Header.h"
#include "CTile.h"
#include "CGame.h"
class CGo :
    public CTile
{
private:

public:
    CGo(istream& file);
    ~CGo();
};

