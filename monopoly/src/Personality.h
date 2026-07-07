#include "Header.h"
#pragma once

class CPlayer;

// 2. The base interface
struct IBoneBrain {
    virtual ~IBoneBrain() = default;
    virtual bool ShouldBuyProperty(const CPlayer* player, int propertyCost) = 0;
    virtual bool ShouldBuildHouse(const CPlayer* player, int houseCost) = 0;
};

// Concrete personalities (use 'class' here to keep things private by default if needed)
class CAggressiveBrain : public IBoneBrain {
public:
    bool ShouldBuyProperty(const CPlayer* player, int propertyCost) override {
        return true;
    }
    bool ShouldBuildHouse(const CPlayer* player, int houseCost) override {
        return true;
    }
};

// 4. The Cautious Personality
class CCautiousBrain : public IBoneBrain {
public:
    // Notice we do NOT write the decision logic here yet. 
    // We just declare the function so the compiler doesn't throw an error.
    bool ShouldBuyProperty(const CPlayer* player, int propertyCost) override;
};