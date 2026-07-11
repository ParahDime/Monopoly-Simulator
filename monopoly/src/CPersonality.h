#include "Header.h"
#include "CGame.h" 
#pragma once

class CPlayer;
class CTile;

struct TradeOffer {
    const CPlayer* Proposer = nullptr;
    const CPlayer* Receiver = nullptr;
    CTile* PropertyOffered = nullptr;
    int CashOffered = 0;
};

//Main interface
struct IBoneBrain {
    virtual ~IBoneBrain() = default;
    virtual bool ShouldBuyProperty(const CPlayer* player, int propertyCost) = 0; //function to determine if property to be bought
    virtual bool ShouldBuildHouse(const CPlayer* player, int houseCost) = 0; //determines if house to be built
    virtual int GetBidAmount(const CPlayer* player,
        int propertyCost,
        int currentHighestBid) = 0;

    virtual bool AssessMyProposedTrade(const CPlayer* player, const TradeOffer& prospectiveOffer, int price, int round) = 0; //ai consider trade value, if worth money
    virtual bool ShouldAcceptIncomingTrade(const CPlayer* player, const TradeOffer& incomingOffer, int propertyCost, int roundsPassed) = 0; //similar to above

    // Shared Execution (The logic that processes and writes to the TradeOffer)
    bool FormulateTradeAttempt(CGame& cGame, vector <CPlayer*>& player, TradeOffer& outOffer, int position, vector<CTile*>& aBoard, int round);
    int GetPropertyMarketValue(CTile* aBoard, const CPlayer* player);
};

// Concrete personalities (use 'class' here to keep things private by default if needed)
class CAggressiveBrain : public IBoneBrain {
public:
    
    bool ShouldBuyProperty(const CPlayer* player, int propertyCost) override;//always buy a property if funds available
    bool ShouldBuildHouse(const CPlayer* player, int houseCost) override; //always buy a house if possible
    int GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) override;

    bool ShouldAcceptIncomingTrade(const CPlayer* player, const TradeOffer& incomingOffer, int propertyCost, int roundsPassed) override;
};

// 4. The Cautious Personality
class CCautiousBrain : public IBoneBrain {
private:
    const int SAFETY_RESERVE = 300;
public:
    // Notice we do NOT write the decision logic here yet. 
    // We just declare the function so the compiler doesn't throw an error.
    bool ShouldBuyProperty(const CPlayer* player, int propertyCost) override;
    bool ShouldBuildHouse(const CPlayer* player, int houseCost) override;
    int GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) override;

    bool ShouldAcceptIncomingTrade(const CPlayer* player, const TradeOffer& incomingOffer, int propertyCost, int roundsPassed);
};

class CChaoticBrain : public IBoneBrain {
private:
    const int SAFETY_RESERVE = 100;
public:
    bool ShouldBuyProperty(const CPlayer* player, int propertyCost) override;
    bool ShouldBuildHouse(const CPlayer* player, int houseCost) override;
    int GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) override;

    bool ShouldAcceptIncomingTrade(const CPlayer* player, const TradeOffer& incomingOffer, int propertyCost, int roundsPassed);
};