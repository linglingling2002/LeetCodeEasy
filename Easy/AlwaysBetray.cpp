#include "AlwaysBetray.h"

int AlwaysBetray::decide(const std::vector<std::pair<int, int>>&, bool) {
    return betrayal;
}
