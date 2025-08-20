#pragma once
#include "IStrategy.h"

class AlwaysBetray : public IStrategy {
public:
    int decide(const std::vector<std::pair<int, int>>&, bool) override;
};
