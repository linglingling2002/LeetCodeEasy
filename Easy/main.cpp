#include <iostream>
#include <memory>
#include <vector>
#include <tuple>
#include <algorithm> // sort

#include "IStrategy.h"
#include "match_utils.h"

#include "AlwaysCooperate.h"
#include "AlwaysBetray.h"
#include "RandomStrategy.h"
#include "TitForTat.h"
#include "TwoTitForTat.h"
#include "TitForTwoTat.h"
#include "Turn.h"

// 单场对战
static std::pair<int, int> playMatch(IStrategy& s1, IStrategy& s2, int rounds) {
	int score1 = 0, score2 = 0;
	std::vector<std::pair<int, int>> history;

	for (int i = 0; i < rounds; ++i) {
		int opt1 = s1.decide(history, true);
		int opt2 = s2.decide(history, false);
		MatchResult res = match(opt1, opt2);
		score1 += res.result1;
		score2 += res.result2;
		std::cout << "option1:" << opt1 << ", score1:" << score1 <<
			"; option2:" << opt2 << ", score2:" << score2 << std::endl;
		history.push_back({ opt1, opt2 });
	}
	return { score1, score2 };
}

// 工厂函数
static std::unique_ptr<IStrategy> createStrategyByChoice(int choice) {
	switch (choice) {
	case 1: return std::make_unique<AlwaysCooperate>();
	case 2: return std::make_unique<AlwaysBetray>();
	case 3: return std::make_unique<RandomStrategy>();
	case 4: return std::make_unique<TitForTat>();
	case 5: return std::make_unique<TwoTitForTat>();
	case 6: return std::make_unique<TitForTwoTat>();
	case 7: return std::make_unique<Turn>();
	default:
		std::cout << "无效编号，默认永远合作\n";
		return std::make_unique<AlwaysCooperate>();
	}
}

static void printMenu() {
	std::cout << "策略编号:\n";
	std::cout << "1. 永远合作\n";
	std::cout << "2. 永远背叛\n";
	std::cout << "3. 随机策略\n";
	std::cout << "4. 以牙还牙\n";
	std::cout << "5. 两报还一报\n";
	std::cout << "6. 一报还两报\n";
	std::cout << "7. 交替策略\n";
}

// 联赛模式
static void leagueMode(int rounds) {
	// 策略原型和名字
	std::vector<std::string> names = {
		"永远合作", "永远背叛", "随机策略", "以牙还牙", "两报还一报", "一报还两报", "交替策略"
	};

	// 比赛总分
	std::vector<int> totalScores(names.size(), 0);

	// 双循环对战
	for (size_t i = 0; i < names.size(); ++i) {
		for (size_t j = 0; j < names.size(); ++j) {
			if (i == j) continue;
			// 新建对象防止历史干扰
			auto p1 = createStrategyByChoice(i + 1);
			auto p2 = createStrategyByChoice(j + 1);
			auto matchRes = playMatch(*p1, *p2, rounds);
			totalScores[i] += matchRes.first;
			totalScores[j] += matchRes.second;
			std::cout << "\n\n";
		}
	}

	// 排序输出
	std::vector<std::pair<std::string, int>> ranking;
	for (size_t i = 0; i < names.size(); ++i) {
		ranking.push_back({ names[i], totalScores[i] });
	}
	std::sort(ranking.begin(), ranking.end(),
		[](auto& a, auto& b) {
			return a.second > b.second;
		});

	std::cout << "\n=== 联赛最终得分榜 ===\n";
	for (size_t rank = 0; rank < ranking.size(); ++rank) {
		std::cout << rank + 1 << ". " << ranking[rank].first << " - "
			<< ranking[rank].second << " 分\n";
	}
}

int main() {
	while (true) {
		std::cout << "\n==== 请选择模式 ====\n";
		std::cout << "1. 单场模式（玩家选择两个策略比赛）\n";
		std::cout << "2. 联赛模式（所有策略互相比赛积分榜）\n";
		std::cout << "请输入模式编号: ";
		int mode;
		std::cin >> mode;

		if (mode == 1) {
			printMenu();
			int choice1, choice2;
			std::cout << "选手1策略编号: ";
			std::cin >> choice1;
			std::cout << "选手2策略编号: ";
			std::cin >> choice2;
			int rounds;
			std::cout << "比赛轮数: ";
			std::cin >> rounds;

			auto p1 = createStrategyByChoice(choice1);
			auto p2 = createStrategyByChoice(choice2);
			auto scoreMatch = playMatch(*p1, *p2, rounds);
			std::cout << "\n最终比分: P1=" << scoreMatch.first << ", P2=" << scoreMatch.second << "\n";
		}
		else if (mode == 2) {
			int rounds;
			std::cout << "请输入每组对战的轮数: ";
			std::cin >> rounds;
			leagueMode(rounds);
		}
		else {
			break;
		}
	}
	return 0;
}
