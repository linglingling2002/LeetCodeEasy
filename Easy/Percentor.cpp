#include "Percentor.h"

int Percentor::decide(const std::vector<std::pair<int, int>>& history, bool isFirstPlayer) {
    if (history.size() < 2) { // 前两轮数据不足，先合作
        return cooperation;
    }

    int changeWhenIChange = 0;
    int totalMyChanges = 0;

    for (size_t i = 0; i + 1 < history.size(); ++i) {
        int myActionNow = isFirstPlayer ? history[i].first : history[i].second;
        int myActionNext = isFirstPlayer ? history[i + 1].first : history[i + 1].second;
        int oppActionNow = isFirstPlayer ? history[i].second : history[i].first;
        int oppActionNext = isFirstPlayer ? history[i + 1].second : history[i + 1].first;

        if (myActionNow != myActionNext) { // 我变了
            totalMyChanges++;
            if (oppActionNow != oppActionNext) { // 他也变了 -> 响应性迹象
                changeWhenIChange++;
            }
        }
    }
    double reactivity = (totalMyChanges == 0) ? 0.0
        : (double)changeWhenIChange / totalMyChanges;

    if (reactivity < 0.3) { // 对我变化无动于衷
        return betrayal;
    }
    else {
        return cooperation;
    }
}
