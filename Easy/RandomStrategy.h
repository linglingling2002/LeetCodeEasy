#pragma once
#include "IStrategy.h"
#include <random>

class RandomStrategy : public IStrategy {
public:
    int decide(const std::vector<std::pair<int, int>>&, bool) override;
};
