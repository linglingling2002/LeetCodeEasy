#include "RandomStrategy.h"

int RandomStrategy::decide(const std::vector<std::pair<int, int>>&, bool) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 1);
    return dist(gen) == 0 ? cooperation : betrayal;
}
