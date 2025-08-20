#pragma once
#include "IStrategy.h"
class TitForTwoTat : public IStrategy {
public:
    TitForTwoTat() : retaliationCount(0) {}
    int decide(const std::vector<std::pair<int, int>>& history, bool isFirstPlayer) override;
private:
    int retaliationCount;
};

