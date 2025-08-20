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
        retaliationCount = 2; // �������ֱ���
    }

    if (retaliationCount > 0) {
        retaliationCount--;
        return betrayal; // ���ڱ�����
    }
    return cooperation;
}
