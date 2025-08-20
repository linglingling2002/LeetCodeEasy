#include "Turn.h"

int Turn::decide(const std::vector<std::pair<int, int>>& history, bool isFirstPlayer) {
	if (history.empty()) return cooperation; // ��һ�ֺ���

	auto last = history.back();
	int myLastAction = isFirstPlayer ? last.first : last.second;

	return 1 - myLastAction; // ֱ����ֵ��ת
}