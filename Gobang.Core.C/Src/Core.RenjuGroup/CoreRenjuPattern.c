#include "CoreRenjuPattern.h"

int getTotalPieceCountOfRenjuPattern(RenjuPattern pattern)
{
    int totalCount = 0;
    for (int i = 0; i < SINGLE_PATTERN_SEAT_COUNT; ++i) {
        if (isRenjuPatternOccupiedAtIndex(pattern, i)) {
            ++totalCount;
        }
    }
    return totalCount;
}