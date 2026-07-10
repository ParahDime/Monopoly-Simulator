#include "Header.h"
#pragma once

class CPlayer;

struct TradeOffer {
    const CPlayer* Proposer = nullptr;
    const CPlayer* Receiver = nullptr;
    std::string PropertyOffered = "";
    std::string PropertyDesired = "";
    int CashOffered = 0;
};

//Main interface
struct IBoneBrain {
    virtual ~IBoneBrain() = default;
    virtual bool ShouldBuyProperty(const CPlayer* player, int propertyCost) = 0; //function to determine if property to be bought
    virtual bool ShouldBuildHouse(const CPlayer* player, int houseCost) = 0; //determines if house to be built
    virtual int GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) = 0; //get the amount for the house (based on place, etc)

    virtual bool AssessMyProposedTrade(const CPlayer* player, const TradeOffer& prospectiveOffer) = 0; //ai consider trade value, if worth money
    virtual bool ShouldAcceptIncomingTrade(const CPlayer* player, const TradeOffer& incomingOffer) = 0; //similar to above

    // Shared Execution (The logic that processes and writes to the TradeOffer)
    bool FormulateTradeAttempt(CGame& cGame, const CPlayer* player, TradeOffer& outOffer);
};

// Concrete personalities (use 'class' here to keep things private by default if needed)
class CAggressiveBrain : public IBoneBrain {
public:
    //always buy a property if available as well as develop them
    bool ShouldBuyProperty(const CPlayer* player, int propertyCost) override {
        return true;
    }
    bool ShouldBuildHouse(const CPlayer* player, int houseCost) override {
        return true;
    }
    int GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) override;
};

// 4. The Cautious Personality
class CCautiousBrain : public IBoneBrain {
public:
    // Notice we do NOT write the decision logic here yet. 
    // We just declare the function so the compiler doesn't throw an error.
    bool ShouldBuyProperty(const CPlayer* player, int propertyCost) override;
    bool ShouldBuildHouse(const CPlayer* player, int houseCost) override;
    int GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) override;
};

class CChaoticBrain : public IBoneBrain {
public:
    bool ShouldBuyProperty(const CPlayer* player, int propertyCost) override;
    bool ShouldBuildHouse(const CPlayer* player, int houseCost) override;
    int GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) override;
};