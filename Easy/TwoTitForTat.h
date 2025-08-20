#pragma once
#include "IStrategy.h"
class TwoTitForTat : public IStrategy {
public:
	int decide(const std::vector<std::pair<int, int>>&, bool) override;
};

