#include "TwoTitForTat.h"

int TwoTitForTat::decide(const std::vector<std::pair<int, int>>& history, bool isFirstPlayer)
{
    int option = cooperation;
    if (history.size() < 2) {
        return cooperation; // 前两局先合作
    }

    auto last = history.back();               // 最后一局
    auto previous = history[history.size() - 2];  // 倒数第二局

    int opp_last = isFirstPlayer ? last.second : last.first;
    int opp_previous = isFirstPlayer ? previous.second : previous.first;

    if (opp_last == betrayal && opp_previous == betrayal) {
        option = betrayal;
    }

    return option;
}
