#pragma once
#include "IStrategy.h"
#include <vector>
class Percentor : public IStrategy {
public:
    int decide(const std::vector<std::pair<int, int>>&, bool) override;
};
