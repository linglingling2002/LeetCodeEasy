// match_utils.h
#pragma once
#include "IStrategy.h"

struct MatchResult {
    int result1;
    int result2;
};

inline MatchResult match(int option1, int option2) {
    if (option1 == option2) {
        return (option1 == cooperation) ? MatchResult{ 3,3 } : MatchResult{ 1,1 };
    }
    else {
        return (option1 == cooperation) ? MatchResult{ 0,5 } : MatchResult{ 5,0 };
    }
}
