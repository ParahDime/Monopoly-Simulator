#include "CPersonality.h"
#include "Board/CTile.h"

//=========================
//   IBoneBrain Functions 
//========================

bool IBoneBrain::FormulateTradeAttempt(CGame& cGame, vector <CPlayer*>& player, TradeOffer& outOffer, int position, vector<CTile*>& aBoard, int round) {

    int currentPosition = player[position]->GetPosition();
    CTile* landedTile = aBoard[currentPosition];

    //Ensure place landed can be bought
    if (!landedTile || !landedTile->IsOwnable()) {
        return false;
    }

    // Check if owned
    int ownerIdx = landedTile->GetOwner();
    // Cannot trade for unowned properties (-1) or properties we already own
    if (ownerIdx == -1 || ownerIdx == aBoard[position]->GetOwner()) {
        return false;
    }

    const CPlayer* targetOwner = player[position];
    if (!targetOwner) return false;

    // Early game (under 5 rounds), bots rarely barter unless completing a set.
    if (round < 5) {
        return false;
    }

    // ------------------------------------------------------------------------
    // SETUP THE OFFER BUNDLE
    // ------------------------------------------------------------------------
    outOffer.Proposer = player[position];
    outOffer.Receiver = targetOwner;

    // Attempt to extract an isolated spare property to throw into the trade matrix
    outOffer.CashOffered = 0;

    return this->AssessMyProposedTrade(player[position], outOffer, landedTile->GetPrice(), round);
}

int IBoneBrain::GetPropertyMarketValue(CTile* aBoard, const CPlayer* player) {

    return aBoard->GetPrice();
}

//===========================
//     Aggro Brain functions
//===========================

bool CAggressiveBrain::ShouldBuyProperty(const CPlayer* player, int propertyCost) {
    if ((player->GetMoney() - propertyCost) >= 0) {
        return true;
    }
    return false;
}

bool CAggressiveBrain::ShouldBuildHouse(const CPlayer* player, int houseCost) {
    // Houses are a secondary luxury; strict rules on cash reserves apply
    if ((player->GetMoney() - houseCost) >= 0) {
        return true;
    }
    return false;
}

int CAggressiveBrain::GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) {
    // Aggressive bidding: Will ruthlessly bid up to 125% of baseline value 
    int maxAggroBid = static_cast<int>(propertyCost * 1.25);
    int nextBid = currentHighestBid + 25;

    if (nextBid <= player->GetMoney() && nextBid <= maxAggroBid) {
        return nextBid;
    }
    return 0;
}

bool CAggressiveBrain::ShouldAcceptIncomingTrade(const CPlayer* player, const TradeOffer& incomingOffer, int propertyCost, int roundsPassed) {
    int offeredAssetValue = 0;
    if (!incomingOffer.PropertyOffered) {
        offeredAssetValue = GetPropertyMarketValue(incomingOffer.PropertyOffered, player);
    }

    int totalIncomingValue = offeredAssetValue + incomingOffer.CashOffered;

    // Aggressive Rule: They demand a premium! They require a 10% profit margin over base cost
    int strictTargetValue = static_cast<int>(propertyCost * 1.10);

    // As time runs thin, they grow slightly more desperate. Reduce premium by 1% per 10 rounds passed.
    int roundDiscount = (roundsPassed / 10) * static_cast<int>(propertyCost * 0.01);
    strictTargetValue = std::max(propertyCost, strictTargetValue - roundDiscount);

    return totalIncomingValue >= strictTargetValue;
}


//======================
//   Cautious Brain functions
//============================

//logic to determine if to buy a property
bool CCautiousBrain::ShouldBuyProperty(const CPlayer* player, int propertyCost) {
    return (player->GetMoney() - propertyCost) >= SAFETY_RESERVE;
}

//logic to determine if to place a house
bool CCautiousBrain::ShouldBuildHouse(const CPlayer* player, int houseCost) {
    return (player->GetMoney() - houseCost) >= (SAFETY_RESERVE + (houseCost * 1.5));
}

// gets a bid amount for a property
int CCautiousBrain::GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) {

    if ((player->GetMoney() - (currentHighestBid + 10)) < SAFETY_RESERVE) {
        return 0; // Drop out
    }
    if (currentHighestBid >= propertyCost) {
        return 0; // Won't overpay past baseline card value
    }
    return currentHighestBid + 10;
}

//assess a trade incoming from a player
bool CCautiousBrain::ShouldAcceptIncomingTrade(const CPlayer* player, const TradeOffer& incomingOffer, int propertyCost, int roundsPassed) {
    // 1. Calculate how much the incoming offer is financially worth
    int offeredAssetValue = 0;
    if (!incomingOffer.PropertyOffered) {
        offeredAssetValue = GetPropertyMarketValue(incomingOffer.PropertyOffered, player);
    }

    // The AI views the trade globally: Property Value + Cash offered
    int totalIncomingValue = offeredAssetValue + incomingOffer.CashOffered;

    // 2. Cautious Rule: Total value coming in MUST be equal or greater than our property's value
    if (totalIncomingValue >= propertyCost) {
        // Double-check liquidity: If the deal somehow forces us to pay cash (negative CashOffered),
        // ensure it doesn't break our strict $300 safety reserve.
        if (incomingOffer.CashOffered < 0 && (player->GetMoney() + incomingOffer.CashOffered < 300)) {
            return false;
        }
        return true;
    }

    return false;
}


//=================================
//   Chaotic Brain functions
//===============================

bool CChaoticBrain::ShouldBuyProperty(const CPlayer* player, int propertyCost) {
    if (player->GetMoney() < propertyCost) return false;

    // Weight formula.
    //If they have double the cost, ratio is 0.5 (50% base shift).
    double financialRatio = static_cast<double>(propertyCost) / player->GetMoney();
    int successChance = 80 - static_cast<int>(financialRatio * 50); // scales roughly 30% to 80%

    return (std::rand() % 100) < successChance;
}

bool CChaoticBrain::ShouldBuildHouse(const CPlayer* player, int houseCost) {
    if (player->GetMoney() < houseCost) return false;

    return (std::rand() % 2) == 0;
}

int CChaoticBrain::GetBidAmount(const CPlayer* player, int propertyCost, int currentHighestBid) {
    if (player->GetMoney() <= currentHighestBid) return 0;

    // Chaotic choice: 25% chance to drop out randomly, 
    // otherwise bids a completely erratic chunk of cash up to total bank capacity
    if ((std::rand() % 4) == 0) return 0;

    int maxAffordableRaise = std::min(50, player->GetMoney() - currentHighestBid);
    if (maxAffordableRaise <= 1) return 0;

    int randomRaise = 1 + (std::rand() % maxAffordableRaise);
    return currentHighestBid + randomRaise;
}


bool CChaoticBrain::ShouldAcceptIncomingTrade(const CPlayer* player, const TradeOffer& incomingOffer, int propertyCost, int roundsPassed) {
    int offeredAssetValue = 0;
    if (!incomingOffer.PropertyOffered) {
        offeredAssetValue = GetPropertyMarketValue(incomingOffer.PropertyOffered, player);
    }

    int totalIncomingValue = offeredAssetValue + incomingOffer.CashOffered;

    // Chaotic baseline is an even value swap (1.0x), but they use a random swing factor
    // Generates a random swing between -20% and +20% value perception deviation
    int randomFluctuation = (std::rand() % 41) - 20;
    int chaoticPerceivedCost = propertyCost + static_cast<int>(propertyCost * (randomFluctuation / 100.0));

    return totalIncomingValue >= chaoticPerceivedCost;
}