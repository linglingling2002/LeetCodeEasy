#pragma once
#include "IStrategy.h"

class AlwaysCooperate : public IStrategy {
public:
    int decide(const std::vector<std::pair<int, int>>&, bool) override;
};
