#ifndef CORE_RENJU_PATTERN_H
#define CORE_RENJU_PATTERN_H

typedef unsigned RenjuPattern;

#define SINGLE_PATTERN_SEAT_COUNT  5

#define RENJU_PATTERN_EMPTY 0

#define addNewPieceToRenjuPatternAtIndex(pattern, index) \
    ((pattern) |= (1 << (SINGLE_PATTERN_SEAT_COUNT - (index) - 1)))

#define isRenjuPatternOccupiedAtIndex(pattern, index) \
    ((pattern) & (1 << (SINGLE_PATTERN_SEAT_COUNT - (index) - 1)))

#define isRenjuPatternFilledWithPieces(pattern) \
    (getTotalPieceCountOfRenjuPattern((pattern)) == SINGLE_PATTERN_SEAT_COUNT)

int getTotalPieceCountOfRenjuPattern(RenjuPattern pattern);

#define RENJU_PATTERN_BASE_SCORE            0
#define RENJU_PATTERN_INVALID_SCORE         0
#define RENJU_PATTERN_MIXED_SCORE           0
#define RENJU_PATTERN_EMPTY_SCORE           7
#define RENJU_PATTERN_FAVORS_SINGLE_SCORE   35
#define RENJU_PATTERN_ADVERSE_SINGLE_SCORE  15
#define RENJU_PATTERN_FAVORS_DOUBLE_SCORE   800
#define RENJU_PATTERN_ADVERSE_DOUBLE_SCORE  400
#define RENJU_PATTERN_FAVORS_TRIPLE_SCORE   15000
#define RENJU_PATTERN_ADVERSE_TRIPLE_SCORE  1800
#define RENJU_PATTERN_FAVORS_QUADRA_SCORE   800000
#define RENJU_PATTERN_ADVERSE_QUADRA_SCORE  100000

#define getFavorsScoreOfPieceCount(COUNT) \
    ((COUNT) == 1 ? RENJU_PATTERN_FAVORS_SINGLE_SCORE : \
    (COUNT) == 2 ? RENJU_PATTERN_FAVORS_DOUBLE_SCORE : \
    (COUNT) == 3 ? RENJU_PATTERN_FAVORS_TRIPLE_SCORE : \
    RENJU_PATTERN_FAVORS_QUADRA_SCORE)

#define getAdverseScoreOfPieceCount(COUNT) \
    ((COUNT) == 1 ? RENJU_PATTERN_ADVERSE_SINGLE_SCORE : \
    (COUNT) == 2 ? RENJU_PATTERN_ADVERSE_DOUBLE_SCORE : \
    (COUNT) == 3 ? RENJU_PATTERN_ADVERSE_TRIPLE_SCORE : \
    RENJU_PATTERN_ADVERSE_QUADRA_SCORE)

#endif // CORE_RENJU_PATTERN_H
