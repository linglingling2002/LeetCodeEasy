// IStrategy.h
#pragma once
#include <vector>
#include <utility>

constexpr auto cooperation = 1;
constexpr auto betrayal = 0;

class IStrategy {
public:
    virtual ~IStrategy() = default;
    virtual int decide(const std::vector<std::pair<int, int>>& history, bool isFirstPlayer) = 0;
};
