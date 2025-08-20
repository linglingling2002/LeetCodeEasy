#include "TitForTat.h"

int TitForTat::decide(const std::vector<std::pair<int, int>>& history, bool isFirstPlayer) {
    if (history.empty()) {
        return cooperation;
    }
    auto lastRound = history.back();
    return isFirstPlayer ? lastRound.second : lastRound.first;
}
