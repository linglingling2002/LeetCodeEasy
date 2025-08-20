#include "AlwaysCooperate.h"

int AlwaysCooperate::decide(const std::vector<std::pair<int, int>>&, bool) {
    return cooperation;
}
