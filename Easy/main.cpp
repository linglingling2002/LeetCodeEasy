#include <iostream>
#include <memory>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

#include "IStrategy.h"
#include "match_utils.h"

#include "AlwaysCooperate.h"
#include "AlwaysBetray.h"
#include "RandomStrategy.h"
#include "TitForTat.h"
#include "TwoTitForTat.h"
#include "TitForTwoTat.h"
#include "Turn.h"
#include "Percentor.h"

// 策略信息结构
struct StrategyInfo {
    int id;              // 固定编号
    std::string name;    // 策略名称
};

// 策略列表（顺序无所谓，id唯一）
static const std::vector<StrategyInfo> strategyList = {
    {1, "永远合作"},
    {2, "永远背叛"},
    {3, "随机策略"},
    {4, "以牙还牙"},
    {5, "两报还一报"},
    {6, "一报还两报"},
    {7, "交替策略"},
    {8, "测敌者"}
};

// 根据ID创建策略实例
static std::unique_ptr<IStrategy> createStrategyByID(int id) {
    switch (id) {
    case 1: return std::make_unique<AlwaysCooperate>();
    case 2: return std::make_unique<AlwaysBetray>();
    case 3: return std::make_unique<RandomStrategy>();
    case 4: return std::make_unique<TitForTat>();
    case 5: return std::make_unique<TwoTitForTat>();
    case 6: return std::make_unique<TitForTwoTat>();
    case 7: return std::make_unique<Turn>();
    case 8: return std::make_unique<Percentor>();
    default:
        std::cout << "无效编号，使用永远合作\n";
        return std::make_unique<AlwaysCooperate>();
    }
}

// 获取策略名
static std::string getStrategyName(int id) {
    for (auto& s : strategyList)
        if (s.id == id) return s.name;
    return "未知策略";
}

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
        // 如不需要调试输出，可注释掉下面行
         std::cout << "o1:" << opt1 << ",s1:" << score1 << "; o2:" << opt2 << ",s2:" << score2 << "\n";
        history.push_back({ opt1, opt2 });
    }
    return { score1, score2 };
}

// ==== 联赛引擎：给一组策略ID计算积分 ====
struct LeagueResult {
    std::vector<int> ids;
    std::vector<int> scores;
};

static LeagueResult runLeagueOnce(const std::vector<int>& ids, int rounds) {
    std::vector<int> totalScores(ids.size(), 0);

    for (size_t i = 0; i < ids.size(); ++i) {
        for (size_t j = 0; j < ids.size(); ++j) {
            if (i == j) continue;
            auto p1 = createStrategyByID(ids[i]);
            auto p2 = createStrategyByID(ids[j]);
            auto matchRes = playMatch(*p1, *p2, rounds);
            totalScores[i] += matchRes.first;
            totalScores[j] += matchRes.second;
            std::cout << "\n\n";
        }
    }

    return { ids, totalScores };
}

// ==== 模式一：单场 ====
static void singleMatchMode() {
    std::cout << "策略编号:\n";
    for (auto& s : strategyList) {
        std::cout << s.id << ". " << s.name << "\n";
    }

    int choice1, choice2;
    std::cout << "选手1策略编号: ";
    std::cin >> choice1;
    std::cout << "选手2策略编号: ";
    std::cin >> choice2;

    int rounds;
    std::cout << "比赛轮数: ";
    std::cin >> rounds;

    auto p1 = createStrategyByID(choice1);
    auto p2 = createStrategyByID(choice2);
    auto scoreMatch = playMatch(*p1, *p2, rounds);
    std::cout << "\n最终比分: P1=" << scoreMatch.first << ", P2=" << scoreMatch.second << "\n";
}

// ==== 模式二：联赛 ====
static void leagueMode(int rounds) {
    std::vector<int> ids;
    for (auto& s : strategyList) ids.push_back(s.id);

    LeagueResult res = runLeagueOnce(ids, rounds);

    // 排序输出
    std::vector<std::pair<int, int>> ranking;
    for (size_t i = 0; i < res.ids.size(); ++i)
        ranking.push_back({ res.ids[i], res.scores[i] });

    std::sort(ranking.begin(), ranking.end(),
        [](auto& a, auto& b) { return a.second > b.second; });

    std::cout << "\n=== 联赛最终得分榜 ===\n";
    for (size_t rank = 0; rank < ranking.size(); ++rank) {
        std::cout << rank + 1 << ". " << getStrategyName(ranking[rank].first)
            << " - " << ranking[rank].second << " 分\n";
    }
}

// ==== 模式三：淘汰赛 ====
static void knockoutMode(int rounds) {
    std::vector<int> aliveIDs;
    for (auto& s : strategyList)
        aliveIDs.push_back(s.id);

    int roundNum = 1;
    while (aliveIDs.size() > 1) {
        std::cout << "\n===== 淘汰赛 第 " << roundNum << " 轮 =====\n";
        LeagueResult res = runLeagueOnce(aliveIDs, rounds);

        // 排序显示本轮成绩
        std::vector<std::pair<int, int>> ranking; // {id, score}
        for (size_t i = 0; i < res.ids.size(); ++i) {
            ranking.push_back({ res.ids[i], res.scores[i] });
        }
        std::sort(ranking.begin(), ranking.end(),
            [](auto& a, auto& b) { return a.second > b.second; });

        for (size_t rank = 0; rank < ranking.size(); ++rank) {
            std::cout << rank + 1 << ". "
                << getStrategyName(ranking[rank].first)
                << " - " << ranking[rank].second << " 分\n";
        }

        // 找到最低分
        int minScore = *std::min_element(res.scores.begin(), res.scores.end());
        int maxScore = *std::max_element(res.scores.begin(), res.scores.end());
        if (minScore == maxScore) {
            std::cout << "并列第一！\n\n";
            return;
        }
        std::vector<int> eliminatedIDs;
        for (size_t i = 0; i < res.scores.size(); ++i) {
            if (res.scores[i] == minScore) {
                eliminatedIDs.push_back(res.ids[i]);
            }
        }

        // 输出淘汰者并移除
        std::cout << "淘汰：";
        for (auto id : eliminatedIDs) {
            std::cout << getStrategyName(id) << " ";
            auto it = std::find(aliveIDs.begin(), aliveIDs.end(), id);
            if (it != aliveIDs.end()) aliveIDs.erase(it);
        }
        std::cout << "\n";

        // 暂停，等待用户按回车继续
        std::cout << "按回车开始下一轮...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        roundNum++;
    }

    std::cout << "\n冠军策略是：" << getStrategyName(aliveIDs.front()) << "！\n";
}

// ==== 主程序入口 ====
int main() {
    while (true) {
        std::cout << "\n==== 请选择模式 ====\n";
        std::cout << "1. 单场模式（玩家选择两个策略比赛）\n";
        std::cout << "2. 联赛模式（所有策略互相比赛积分榜）\n";
        std::cout << "3. 淘汰赛模式（每轮淘汰最低分）\n";
        std::cout << "其他数字退出\n";
        std::cout << "请输入模式编号: ";
        int mode;
        std::cin >> mode;

        if (mode == 1) {
            singleMatchMode();
        }
        else if (mode == 2) {
            int rounds;
            std::cout << "请输入每组对战的轮数: ";
            std::cin >> rounds;
            leagueMode(rounds);
        }
        else if (mode == 3) {
            int rounds;
            std::cout << "请输入每组对战的轮数: ";
            std::cin >> rounds;
            knockoutMode(rounds);
        }
        else {
            break;
        }
    }
    return 0;
}