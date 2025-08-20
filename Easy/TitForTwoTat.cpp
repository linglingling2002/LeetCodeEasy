#include "TitForTwoTat.h"

int TitForTwoTat::decide(const std::vector<std::pair<int, int>>& history, bool isFirstPlayer)
{
    if (history.empty()) {
        retaliationCount = 0;
        return cooperation;
    }

    auto lastRound = history.back();
    int oppLast = isFirstPlayer ? lastRound.second : lastRound.first;

    if (oppLast == betrayal) {
        retaliationCount = 2; // 启动两轮报复
    }

    if (retaliationCount > 0) {
        retaliationCount--;
        return betrayal; // 处于报复期
    }
    return cooperation;
}
