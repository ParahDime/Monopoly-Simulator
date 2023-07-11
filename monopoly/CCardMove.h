#pragma once
#include "CCard.h"
class CCardMove :
    public CCard
{
private:
    bool isSpecific = false;
    int mTyping = 0; //specific type
    string mNaming = " "; //specific name
public:
    CCardMove(istream& file);
    ~CCardMove();

    void GetText();
    void SetSpecific(bool tSpecific);
    bool GetSpecific();

    //get and set name
    void SetNaming();
    string GetNaming();
    //get and set typing on card
    void SetTyping();
    int GetTyping();

    friend istream& operator >> (istream& inputStream, CCardMove& cCardMove);
};

