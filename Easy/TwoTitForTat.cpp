#include "TwoTitForTat.h"

int TwoTitForTat::decide(const std::vector<std::pair<int, int>>& history, bool isFirstPlayer)
{
    int option = cooperation;
    if (history.size() < 2) {
        return cooperation; // ǰ�����Ⱥ���
    }

    auto last = history.back();               // ���һ��
    auto previous = history[history.size() - 2];  // �����ڶ���

    int opp_last = isFirstPlayer ? last.second : last.first;
    int opp_previous = isFirstPlayer ? previous.second : previous.first;

    if (opp_last == betrayal && opp_previous == betrayal) {
        option = betrayal;
    }

    return option;
}
